#include <gui/screens/InvalidLicenseScreen.hpp>
#include <Minecraft.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <string.h>
InvalidLicenseScreen::InvalidLicenseScreen(int32_t err, int8_t v8) {
	this->err = err;
	this->field_6C = v8;
	this->field_58 = "";
	this->field_5C = "";
	this->field_60 = "";
	this->okButton = 0;
	this->buyButton = 0;
	this->field_70 = 0;
}
InvalidLicenseScreen::~InvalidLicenseScreen() {
	if(this->okButton) delete this->okButton;
	if(this->buyButton) delete this->buyButton;
}
void InvalidLicenseScreen::render(int32_t a2, int32_t a3, float a4) {
	this->renderDirtBackground(0);
	this->drawCenteredString(this->minecraft->font, this->field_58, this->width / 2, this->field_70, 0xFFFFFF);
	this->drawCenteredString(this->minecraft->font, this->field_5C, this->width / 2, this->field_70 + 24, 0xFFFFFF);
	this->drawCenteredString(this->minecraft->font, this->field_60, this->width / 2, this->field_70 + 60, 0xFFFFFF);
	Screen::render(a2, a3, a4);
}
void InvalidLicenseScreen::init() {
	uint32_t err; // r6

	this->okButton = new Touch::TButton(1, "Ok", 0);
	this->buyButton = new Touch::TButton(2, "Buy", 0);
	this->okButton->init(this->minecraft);
	this->buyButton->init(this->minecraft);
	if(this->field_6C) {
		this->okButton->maybeTextOnButton = "Quit";
	}
	err = this->err;
	if(err > 1) {
		char v9[20]; // [sp+8h] [bp-30h] BYREF
		memset(v9, 0, sizeof(v9));
		sprintf(v9, "%d", err);
		this->field_58 = "License verification failed (error ";
		this->field_58 += v9;
		this->field_58 += ")";
		this->field_5C = "Try again later.";
		this->field_60 = "You need to be connected to the internet\n";
		this->field_60 += "once while you start the game.";
	}
	this->buttons.push_back(this->okButton);
	this->field_2C.push_back(this->okButton);
	if(this->field_6C) {
		this->buttons.push_back(this->buyButton);
		this->field_2C.push_back(this->buyButton);
	}
}
void InvalidLicenseScreen::setupPositions() {
	Touch::TButton* okButton;  // r1
	Touch::TButton* buyButton; // r2
	Touch::TButton* v3;		   // r3
	int32_t v4;				   // r2

	okButton = this->okButton;
	buyButton = this->buyButton;
	this->field_70 = this->height / 5 - 18;
	buyButton->width = 200;
	okButton->width = 200;
	v3 = this->okButton;
	v4 = (this->width - v3->width) / 2;
	this->buyButton->posX = v4;
	v3->posX = v4;
	this->buyButton->posY = this->field_70 + 84;
	this->okButton->posY = this->buyButton->posY + this->buyButton->height + 4;
	if(!this->field_6C) {
		this->okButton->posY -= 24;
	}
}
void InvalidLicenseScreen::tick() {
}
void InvalidLicenseScreen::buttonClicked(Button* a2) {
	if(a2->buttonID == this->okButton->buttonID) {
		this->minecraft->quit();
	}
	if(a2->buttonID == this->buyButton->buttonID) {
		this->minecraft->platform()->buyGame();
	}
}
