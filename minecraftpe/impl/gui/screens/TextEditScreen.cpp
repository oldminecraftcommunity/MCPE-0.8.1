#include <gui/screens/TextEditScreen.hpp>
#include <Minecraft.hpp>
#include <level/Level.hpp>
#include <network/RakNetInstance.hpp>
#include <rendering/Font.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <tile/entity/SignTileEntity.hpp>
#include <util/Util.hpp>

TextEditScreen::TextEditScreen(SignTileEntity* a2)
	: Screen()
	, doneButton(1, "") {
	this->field_54 = 0;
	this->signX = a2->posX;
	this->signY = a2->posY;
	this->signZ = a2->posZ;
	this->tickCounter = 0;
	this->currentLine = 0;
}
void TextEditScreen::failedToFindSignEntity() {
	this->minecraft->platform()->hideKeyboard();
	this->minecraft->setScreen(0);
}

TextEditScreen::~TextEditScreen() {
}
void TextEditScreen::render(int32_t a2, int32_t a3, float a4) {
	TileEntity* te;		  // r0
	SignTileEntity* v9;	  // r6
	Minecraft* minecraft; // r2
	float v12;			  // s16
	int32_t v13;		  // r5
	int32_t v15;		  // r0
	int32_t v16;		  // r0

	te = this->minecraft->level->getTileEntity(this->signX, this->signY, this->signZ);
	v9 = (SignTileEntity*)te;
	if(te && te->type == 4) {
		glDepthMask(0);
		this->renderBackground(0);
		glDepthMask(1u);
		glPushMatrix();
		glDisable(0xB44u);
		glLoadIdentity();
		glMatrixMode(0x1701u);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, (float)this->minecraft->field_1C, (float)this->minecraft->field_20, 0.0, -1.0,
				1.0); //actually glOrthof
		glMatrixMode(0x1700u);
		this->minecraft->texturesPtr->loadAndBindTexture("item/sign.png");
		glColor4f(1.0, 1.0, 1.0, 1.0);
		minecraft = this->minecraft;
		v12 = (float)(minecraft->field_20 / 64) * 0.9;
		glTranslatef((float)minecraft->field_1C * 0.5, 5.0, 0.0);
		glScalef(v12, v12, 1.0);
		Tesselator::instance.begin(4);
		Tesselator::instance.vertexUV(-32.0, 0.0, 0.0, 0.03126, 0.06249);
		Tesselator::instance.vertexUV(32.0, 0.0, 0.0, 0.39063, 0.06249);
		Tesselator::instance.vertexUV(32.0, 32.0, 0.0, 0.39063, 0.4374);
		Tesselator::instance.vertexUV(-32.0, 32.0, 0.0, 0.03126, 0.4374);
		Tesselator::instance.draw(1);
		v9->field_6C = this->currentLine;
		v13 = 0;
		glTranslatef(0.0, 2.0, 0.0);
		glScalef(0.72727, 0.72727, 1.0);
		do {
			std::string ss = v9->textLines[v13];
			if(v13 == v9->field_6C && Util::utf8len(ss) <= 13) {
				std::string v20 = "";
				v20 += "> ";
				v20 += ss;
				v20 += " <";
				v15 = this->font->width(v20);
				this->font->draw(v20, -(float)((float)v15 * 0.5), (float)v13 * 10.0, -16777216, 0);
			} else {
				v16 = this->font->width(ss);
				this->font->draw(ss, -(float)((float)v16 * 0.5), (float)v13 * 10.0, -16777216, 0);
			}
			++v13;
		} while(v13 != 4);
		v9->field_6C = -1;
		glPopMatrix();
		glMatrixMode(0x1701u);
		glPopMatrix();
		glMatrixMode(0x1700u);
		Screen::render(a2, a3, a4);
		glEnable(0xB44u);
	} else {
		this->failedToFindSignEntity();
	}
}
void TextEditScreen::init() {
	TileEntity* te; // r0

	Screen::init();
	te = this->minecraft->level->getTileEntity(this->signX, this->signY, this->signZ);
	if(te) {
		if(te->type == 4) {
			this->minecraft->platform()->showKeyboard(&((SignTileEntity*)te)->textLines[this->currentLine], 15, 0);
		}
	}
	this->field_54 = 1;
	ImageDef a2;
	a2.field_0 = "gui/spritesheet.png";
	a2.field_4 = 0;
	a2.height = 18.0;
	a2.width = 18.0;
	a2.field_8 = 1;
	a2.field_14 = 60;
	a2.field_24 = 1;
	a2.field_1C = 18;
	a2.field_20 = 18;
	a2.field_18 = 0;

	this->doneButton.setImageDef(a2, 1);
	this->doneButton.field_64 = 0;
	this->buttons.emplace_back(&this->doneButton);
}
void TextEditScreen::setupPositions() {
	this->doneButton.height = 19;
	this->doneButton.width = 19;
	this->doneButton.posX = this->width - 19;
	this->doneButton.posY = 0;
}
bool_t TextEditScreen::handleBackEvent(bool_t a2) {
	TileEntity* tile; // r0
	TileEntity* v4;	  // r5
	Packet* v5;		  // r0

	tile = this->minecraft->level->getTileEntity(this->signX, this->signY, this->signZ);
	v4 = tile;
	if(tile && tile->type == 4) {
		tile->setChanged();
		this->minecraft->rakNetInstance->send(v4->getUpdatePacket());
		this->minecraft->platform()->hideKeyboard();
		this->minecraft->setScreen(0);
	} else {
		this->failedToFindSignEntity();
	}
	return 1;
}
void TextEditScreen::tick() {
	++this->tickCounter;
}
void TextEditScreen::lostFocus() {
}
void TextEditScreen::setTextboxText(const std::string& a2) {
	TileEntity* te; // r0

	te = this->minecraft->level->getTileEntity(this->signX, this->signY, this->signZ);
	if(te) {
		if(te->type == 4) {
			((SignTileEntity*)te)->textLines[this->currentLine] = a2;
		}
	}
}
void TextEditScreen::buttonClicked(Button* a2) {
	if(a2 == &this->doneButton) {
		this->handleBackEvent(1);
	}
}
void TextEditScreen::keyPressed(int32_t a2) {
	TileEntity* te;		 // r0
	SignTileEntity* v5;	 // r5
	int32_t currentLine; // r3
	int32_t v8;			 // r0
	int32_t v10;		 // r3

	te = this->minecraft->level->getTileEntity(this->signX, this->signY, this->signZ);
	v5 = (SignTileEntity*)te;
	if(!te || te->type != 4) {
		this->failedToFindSignEntity();
		return;
	}
	if(a2 == 8) {
		currentLine = this->currentLine;
		if(v5->textLines[currentLine].size() != 0) {
			v8 = Util::utf8len(v5->textLines[currentLine]);
			v5->textLines[currentLine] = Util::utf8substring(v5->textLines[currentLine], 0, v8 - 1);
			return;
		}
		v10 = currentLine - 1;
		if(v10 < 0) {
			v10 = 3;
		}
		goto LABEL_9;
	}
	if(a2 == 13) {
		v10 = (this->currentLine + 1) % 4;
LABEL_9:
		this->currentLine = v10;
		this->minecraft->platform()->updateTextBoxText(v5->textLines[this->currentLine]);
		return;
	}
	Screen::keyPressed(a2);
}
void TextEditScreen::keyboardNewChar(const std::string& a2, bool_t a3) {
	SignTileEntity* te; // r0

	te = (SignTileEntity*)this->minecraft->level->getTileEntity(this->signX, this->signY, this->signZ);
	if(te && te->type == 4) {
		std::string src = te->textLines[this->currentLine];
		src += a2;
		if(Util::utf8len(src) <= 15) {
			te->textLines[this->currentLine] = src;
		}
	} else {
		this->failedToFindSignEntity();
	}
}
