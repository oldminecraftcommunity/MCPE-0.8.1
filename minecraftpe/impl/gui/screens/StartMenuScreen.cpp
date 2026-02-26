#include <gui/screens/StartMenuScreen.hpp>
#include <Minecraft.hpp>
#include <gui/screens/InvalidLicenseScreen.hpp>
#include <gui/screens/OptionsScreen.hpp>
#include <gui/screens/PlayScreen.hpp>
#include <rendering/Font.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <util/Common.hpp>

StartMenuScreen::StartMenuScreen()
	: Screen()
	, startGameButton(2, 0, 0, 60, 24, "Start Game")
	, joinGameButton(3, 0, 0, 160, 24, "Join Game")
	, optionsButton(4, 0, 0, 78, 22, "Options")
	, createButton(999, 0, 0, 78, 22, "Create")
	, buyButton(5, 0, 0, 78, 22, "Buy") {
	this->mojangABMaybe = "";
	this->gameVersion = "";
}
void StartMenuScreen::_updateLicense() {
	int32_t lide;		  // r0
	int32_t v3;			  // r6
	bool_t v4;			  // r3
	int8_t v6;			  // r0
	Minecraft* minecraft; // r7
	int8_t v8;			  // r8

	lide = this->minecraft->getLicenseId();
	v3 = lide;
	if(lide < 0) {
		v4 = 0;
	} else {
		if((uint32_t)lide > 1) {
			v6 = this->minecraft->platform()->hasBuyButtonWhenInvalidLicense();
			minecraft = this->minecraft;
			v8 = v6;
			minecraft->setScreen(new InvalidLicenseScreen(v3, v8));
			return;
		}
		v4 = 1;
	}
	this->optionsButton.active = v4;
	this->startGameButton.active = v4;
	this->joinGameButton.active = v4;
}

StartMenuScreen::~StartMenuScreen() {
}
void StartMenuScreen::render(int32_t a2, int32_t a3, float a4) {
	TextureData* td; // r5
	float width;	 // s15
	float v12;		 // s17
	float v13;		 // s16
	float v14;		 // s15
	float height;	 // s14
	float v16;		 // s19
	float v17;		 // s16

	this->renderMenuBackground(a4);
	td = this->minecraft->texturesPtr->loadAndGetTextureData("gui/title.png");
	if(td) {
		this->minecraft->texturesPtr->loadAndBindTexture("gui/title.png");
		width = (float)td->width;
		v12 = (float)this->width * 0.5;
		v13 = width * 0.5;
		if(v12 <= (float)(width * 0.5)) {
			v13 = (float)this->width * 0.5;
		}
		v14 = (float)(v13 + v13) / width;
		height = (float)td->height;
		glColor4f(1.0, 1.0, 1.0, 1.0);
		Tesselator::instance.begin(4);
		v16 = v12 - v13;
		Tesselator::instance.vertexUV(v12 - v13, (float)(v14 * height) + 4.0, this->zLayer, 0.0, 1.0);
		v17 = v12 + v13;
		Tesselator::instance.vertexUV(v17, (float)(v14 * height) + 4.0, this->zLayer, 1.0, 1.0);
		Tesselator::instance.vertexUV(v17, 4.0, this->zLayer, 1.0, 0.0);
		Tesselator::instance.vertexUV(v16, 4.0, this->zLayer, 0.0, 0.0);
		Tesselator::instance.draw(1);
	}
	this->drawString(this->font, this->gameVersion, this->field_150, 62, 0xFFCCCCCC);
	this->drawString(this->font, this->mojangABMaybe, this->field_148, this->height - 10, 0xFFFFFF);
	Screen::render(a2, a3, a4);
}
void StartMenuScreen::init() {
	this->buttons.emplace_back(&this->startGameButton);
	this->buttons.emplace_back(&this->joinGameButton);
	this->field_2C.emplace_back(&this->startGameButton);
	this->field_2C.emplace_back(&this->joinGameButton);
	this->buttons.emplace_back(&this->optionsButton);
	this->field_2C.emplace_back(&this->optionsButton);
	this->mojangABMaybe = "\xFFMojang AB";
	this->gameVersion = Common::getGameVersionString();
	this->optionsButton.active = 0;
	this->startGameButton.active = 0;
	this->joinGameButton.active = 0;
}
void StartMenuScreen::setupPositions() {
	int32_t width;		  // r5
	int32_t v3;			  // r3
	int32_t v4;			  // r2
	int32_t v5;			  // r3
	int32_t v6;			  // r2
	int32_t v7;			  // r3
	int32_t v8;			  // r3
	int32_t v9;			  // r0
	Minecraft* minecraft; // r3
	int32_t v11;		  // r5

	width = this->width;
	v3 = this->height / 2;
	this->startGameButton.posY = v3 - 3;
	v4 = v3 + 25;
	v3 += 55;
	this->optionsButton.posY = v3;
	this->buyButton.posY = v3;
	this->createButton.posY = v3;
	v5 = this->startGameButton.width;
	this->joinGameButton.posY = v4;
	v6 = this->optionsButton.width;
	this->startGameButton.posX = (width - v5) / 2;
	v7 = (width - this->joinGameButton.width) / 2;
	this->joinGameButton.posX = v7;
	this->optionsButton.posX = v7;
	v8 = v7 + v6 + 4;
	this->buyButton.posX = v8;
	this->createButton.posX = v8;
	v9 = this->minecraft->font->width(this->mojangABMaybe);
	minecraft = this->minecraft;
	this->field_148 = width - v9 - 1;
	v11 = this->width;
	this->field_150 = (v11 - minecraft->font->width(this->gameVersion)) / 2;
}
bool_t StartMenuScreen::handleBackEvent(bool_t a2) {
	this->minecraft->quit();
	return 1;
}
void StartMenuScreen::tick() {
	this->_updateLicense();
}
bool_t StartMenuScreen::isInGameScreen() {
	return 0;
}
void StartMenuScreen::buttonClicked(Button* a2) {
	if(a2->buttonID == this->startGameButton.buttonID) {
		this->minecraft->screenChooser.setScreen(SELECT_WORLD_SCREEN);
	}
	if(a2->buttonID == this->joinGameButton.buttonID) {
		this->minecraft->locateMultiplayer();
		this->minecraft->setScreen(new PlayScreen(1));
	}
	if(a2->buttonID == this->optionsButton.buttonID) {
		this->minecraft->setScreen(new OptionsScreen(0));
	}
	if(a2->buttonID == this->buyButton.buttonID) {
		this->minecraft->platform()->buyGame();
	}
}
