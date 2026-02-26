#include <gui/elements/LocalServerListItemElement.hpp>
#include <level/LevelSummary.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <input/Mouse.hpp>
#include <gui/Gui.hpp>
#include <math.h>
#include <utils.h>
#include <util/IntRectangle.hpp>
#include <Minecraft.hpp>
#include <rendering/Font.hpp>
#include <rendering/Textures.hpp>
#include <network/PingedCompatibleServer.hpp>
#include <gui/buttons/ImageWithBackground.hpp>
#include <ExternalServerFile.hpp>
#include <gui/screens/PlayScreen.hpp>
#include <gui/screens/Touch_DeleteWorldScreen.hpp>
#include <gui/screens/DisconnectionScreen.hpp>
#include <gui/screens/ProgressScreen.hpp>
#include <sstream>
#include <util/Util.hpp>
#include <util/ParameterStringify.hpp>
#include <level/LevelSettings.hpp>

LocalServerListItemElement::LocalServerListItemElement(Minecraft* a2, ExternalServer a3, bool_t editing, PlayScreen* a5)
	: GuiElement(1, 1, 0, 0, 24, 24) {
	this->field_24 = this->field_28 = 0; //XXX doesnt seem to be in mcpe
	this->field_2C = 0;
	this->field_30 = 0;
	this->deleteElementButton = 0;
	this->field_3C = 0;
	this->levelSummary = 0;
	this->isEditing = editing;
	this->field_50 = 0;
	this->field_54 = a5;
	this->height = 32;
	this->server = new ExternalServer(a3);
	if(editing) {
		this->deleteElementButton = new ImageWithBackground(-1);
		this->deleteElementButton->init(a2->texturesPtr, 32, 32, {112, 0, 8, 67}, {120, 0, 8, 67}, 2, 2, "gui/spritesheet.png");
		ImageDef v16;
		v16.field_0 = "gui/gui.png";
		v16.field_24 = 1;
		v16.width = 11.0;
		v16.height = 11.0;
		v16.field_14 = 182;
		v16.field_18 = 10;
		v16.field_1C = 11;
		v16.field_20 = 11;
		this->deleteElementButton->setImageDef(v16, 0);
		this->deleteElementButton->width = 32;
		this->deleteElementButton->height = 32;
		this->deleteElementButton->setupPositions();
	}
}
LocalServerListItemElement::LocalServerListItemElement(Minecraft* a2, const LevelSummary& a3, bool_t a4)
	: GuiElement(1, 1, 0, 0, 24, 24) {
	this->field_24 = this->field_28 = 0; //XXX doesnt seem to be in mcpe
	this->field_2C = 0;
	this->field_30 = 0;
	this->deleteElementButton = 0;
	this->server = 0;
	this->isEditing = a4;
	this->field_50 = 0;
	this->field_54 = 0;
	this->height = 32;
	this->field_3C = 0;
	this->levelSummary = new LevelSummary(a3);
	if(a4) {
		this->deleteElementButton = new ImageWithBackground(-1);
		this->deleteElementButton->init(a2->texturesPtr, 32, 32, {112, 0, 8, 67}, {120, 0, 8, 67}, 2, 2, "gui/spritesheet.png");
		ImageDef v15;
		v15.field_0 = "gui/gui.png";
		v15.field_24 = 1;
		v15.width = 11.0;
		v15.height = 11.0;
		v15.field_14 = 182;
		v15.field_18 = 10;
		v15.field_1C = 11;
		v15.field_20 = 11;
		this->deleteElementButton->setImageDef(v15, 0);
		this->deleteElementButton->width = 32;
		this->deleteElementButton->height = 32;
		this->deleteElementButton->setupPositions();
		std::stringstream v16;
		v16 << this->levelSummary->field_10;
		this->field_44 = v16.str();
		this->field_48 = a2->font->width(this->field_44);
	}
}
LocalServerListItemElement::LocalServerListItemElement(const PingedCompatibleServer& a2)
	: GuiElement(1, 1, 0, 0, 24, 24) {
	this->field_24 = this->field_28 = 0; //XXX doesnt seem to be in mcpe
	this->field_2C = 0;
	this->field_30 = 0;
	this->deleteElementButton = 0;
	this->server = 0;
	this->field_50 = 0;
	this->field_54 = 0;
	this->height = 32;
	this->field_3C = new PingedCompatibleServer(a2);
	this->levelSummary = 0;
}
std::string LocalServerListItemElement::getLastPlayedString() {
	int32_t v3; // r0
	char_t s[32]; // [sp+4h] [bp-34h] BYREF

	if(!this->levelSummary) {
		return "";
	}
	v3 = getEpochTimeS() - this->levelSummary->field_8;
	if(v3 > 86399) {
		if(v3 > 172799) {
			if(v3 > 604799) {
				if(v3 > 2419199) {
					return "long ago";
				}
				sprintf(s, "%d weeks ago", v3 / 604800);
			} else {
				sprintf(s, "%d days ago", v3 / 86400);
			}
			return s;
		} else {
			return "Yesterday";
		}
	} else {
		return "Today";
	}
}
void LocalServerListItemElement::init(Minecraft* a2) {
	Touch::TButton* v4 = new Touch::TButton(1, "", 0);
	v4->init(a2, "gui/spritesheet.png", {8, 32, 8, 8}, {0, 32, 8, 8}, 2, 2, 120, 32);
	this->field_2C = v4;
}

LocalServerListItemElement::~LocalServerListItemElement() {
	if(this->server) {
		delete this->server;
		this->server = 0;
	}

	if(this->field_3C) {
		delete this->field_3C;
		this->field_3C = 0;
	}
	if(this->levelSummary) {
		delete this->levelSummary;
		this->levelSummary = 0;
	}

	if(this->deleteElementButton) {
		delete this->deleteElementButton;
		this->deleteElementButton = 0;
	}

	if(this->field_2C) {
		delete this->field_2C;
		this->field_2C = 0;
	}
}
void LocalServerListItemElement::tick(Minecraft* a2) {
	float x; // s16
	float y; // s15
	Button* deleteElementButton; // r0
	Button* v6; // r3

	x = (float)Mouse::getX() * Gui::InvGuiScale;
	y = (float)Mouse::getY() * Gui::InvGuiScale;
	if(fabsf(x - this->field_24) > 20.0 || fabsf(y - this->field_28) > 20.0) {
		deleteElementButton = this->field_2C;
		v6 = this->field_30;
		if(deleteElementButton == v6 || (deleteElementButton = this->deleteElementButton) != 0 && deleteElementButton == v6) {
			deleteElementButton->released((int32_t)x, (int32_t)y);
		}
		this->field_30 = 0;
	}
	++this->field_50;
}
void LocalServerListItemElement::render(Minecraft* a2, int32_t a3, int32_t a4) {
	ImageWithBackground* deleteElementButton; // r2
	int32_t width; // r8
	bool_t isPressed; // r0
	LevelSummary* levelSummary; // r9
	int32_t v12; // r0
	int32_t v14; // r11
	ImageWithBackground* v15; // r3
	Font* font; // r6
	int32_t v17; // r11
	PingedCompatibleServer* v20; // r3
	ExternalServer* server; // r3
	ExternalServer* v23; // r3
	ImageWithBackground* v25; // r3
	char_t v29[128]; // [sp+2Ch] [bp-B4h] BYREF

	if(this->levelSummary && (deleteElementButton = this->deleteElementButton) != 0) {
		width = this->width - deleteElementButton->width;
	} else {
		width = this->width;
	}
	this->field_2C->posX = this->posX;
	this->field_2C->posY = this->posY;
	this->field_2C->width = width;
	this->field_2C->render(a2, a3, a4);
	isPressed = this->field_2C->isPressed(a3, a4);
	levelSummary = this->levelSummary;
	if(isPressed) {
		v12 = 0xFFFFA0;
	} else {
		v12 = 0xFFFFFFFF;
	}
	if(levelSummary) {
		a2->font->drawShadow(levelSummary->field_4, (float)this->posX + 5.0, (float)this->posY + 5.0, v12);
		std::string ss = this->levelSummary->field_C == 1 ? "Creative" : "Survival";
		v14 = a2->font->width(ss);
		a2->font->drawShadow(ss, (float)this->posX + 5.0, (float)this->posY + 16.0, 0xFFBBBBBB);
		a2->font->drawShadow(this->getLastPlayedString(), (float)((float)((float)this->posX + 5.0) + (float)v14) + 10.0, (float)this->posY + 16.0, 0xFFBBBBBB);
		v15 = this->deleteElementButton;
		if(v15) {
			v15->posX = this->posX + this->width - v15->width;
			this->deleteElementButton->posY = this->posY;
			this->deleteElementButton->render(a2, a3, a4);
		}
		if(this->isEditing) {
			font = a2->font;
			v17 = width + this->posX;
			font->drawShadow("Seed:", (float)(v17 - font->width("Seed:")) - 5.0, (float)this->posY + 5.0, 0xFFBBBBBB);
			a2->font->drawShadow(this->field_44, (float)(width + this->posX - this->field_48) - 5.0, (float)this->posY + 16.0, 0xFFBBBBBB);
		}
	} else {
		v20 = this->field_3C;
		if(v20) {
			a2->font->drawShadow(v20->field_0, (float)this->posX + 5.0, (float)this->posY + 5.0, -4473857);
			this->field_3C->field_4.ToString(0, v29, '|');
			a2->font->drawShadow(
				std::string("World on wifi: ").append(v29),
				(float)this->posX + 5.0,
				(float)this->posY + 16.0,
				0xFFBBBBBB);
			a2->texturesPtr->loadAndBindTexture("gui/spritesheet.png");
			glColor4f(1.0, 1.0, 1.0, 1.0);
			this->blit(
				(float)this->width - 14.0f,
				(float)this->posY + 9.0f,
				192,
				-24 * (this->field_50 / 4 % 3) + 48,
				12.0,
				12.0,
				24,
				24);
		}
		else
		{
			server = this->server;
			if ( !server )
			{
				return;
			}
			a2->font->drawShadow(
				server->field_4,
				(float)this->posX + 5.0,
				(float)this->posY + 5.0,
				v12);
			//copyRawCharArrayInside(&v28, "Survival");
			v23 = this->server;
			if ( v23->field_8.size() <= 0x80u )
			{
				sprintf(v29, "%s:%d", v23->field_8.c_str(), v23->field_C);
			}
			else
			{
				sprintf(v29, "...:%d", v23->field_C);
			}
			a2->font->drawShadow(
				v29,
				(float)this->posX + 5.0,
				(float)this->posY + 16.0,
				-4473925);
			if ( this->isEditing )
			{
				v25 = this->deleteElementButton;
				if ( v25 )
				{
					v25->posX = this->posX + this->width - v25->width;
					this->deleteElementButton->posY = this->posY;
					this->deleteElementButton->render(
						a2,
						a3,
						a4);
				}
			}
		}
	}
}
void LocalServerListItemElement::mouseClicked(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5){
	float v9; // s17
	int32_t v10; // s15
	ImageWithBackground *deleteElementButton; // r0
	float v12; // s16
	Button *v13; // r0

	v9 = (float)Mouse::getX() * Gui::InvGuiScale;
	v10 = Mouse::getY();
	deleteElementButton = this->deleteElementButton;
	v12 = (float)v10 * Gui::InvGuiScale;
	if ( deleteElementButton
	   && deleteElementButton->clicked(a2, a3, a4) )
	{
		v13 = this->deleteElementButton;
		this->field_24 = v9;
		this->field_28 = v12;
	}
	else
	{
		if ( !this->field_2C->clicked(a2, a3, a4) )
		{
			return;
		}
		this->field_24 = v9;
		this->field_28 = v12;
		v13 = this->field_2C;
	}
	this->field_30 = v13;
	v13->setPressed();
}
void LocalServerListItemElement::mouseReleased(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5)
{
	if(this->deleteElementButton && this->deleteElementButton == this->field_30) {
		if(this->deleteElementButton->clicked(a2, a3, a4)) {
			if(this->server) {
				a2->externalServerFile->removeServer(this->server->field_0);
				this->field_54->field_50 = 1;
			} else {
				a2->setScreen(new Touch::DeleteWorldScreen(*this->levelSummary));
			}
			return;
		}
		this->deleteElementButton->released(a3, a4);
		this->field_30 = 0;
		return;
	}
	if(this->field_30 != this->field_2C) {
		return;
	}

	if(!this->field_30->clicked(a2, a3, a4)) {
		this->field_2C->released(a3, a4);
		this->field_30 = 0;
		return;
	}

	if(this->field_3C || this->server) {
		if(this->server) {
			if(a2->platform()->isNetworkEnabled(1)) {
				PingedCompatibleServer v43;
				v43.field_4.FromStringExplicitPort(this->server->field_8.c_str(), this->server->field_C, 0);
				v43.field_0 = this->server->field_4.c_str();
				a2->joinMultiplayer(PingedCompatibleServer(v43), 0);
				a2->setScreen(new ProgressScreen());
				std::string v38_;
				{ //TODO probably some inlined function - ParameterStringify::something ???
					std::string v33 = "{\"%\": \"%\"}";
					std::vector<std::string> v37;
					{
						std::stringstream v38;
						v38 << "server_type";
						v37.emplace_back(v38.str());
						std::stringstream v40;
						v40 << "External";
						v37.emplace_back(v40.str());
					}
					v38_ = Util::simpleFormat(v33, v37);
				}
				a2->platform()->statsTrackData("start_game", v38_);
				return;
			}
			a2->setScreen(new DisconnectionScreen("You need to be connected through Wifi to play on External servers"));
		} else {
			a2->joinMultiplayer(*this->field_3C, 0);
			a2->setScreen(new ProgressScreen());
			//TODO ParameterStringify::stringifyNext()
			printf("LocalServerListItemElement::mouseReleased - connect to local server - statsTrackData - not implemented\n");
		}
	}else{
		a2->selectLevel(this->levelSummary->field_0, this->levelSummary->field_4, LevelSettings{-1, -1});
		a2->hostMultiplayer(19132);
		a2->setScreen(new ProgressScreen());

		printf("LocalServerListItemElement::mouseReleased - join world - statsTrackData - not implemented\n");
	}
}
