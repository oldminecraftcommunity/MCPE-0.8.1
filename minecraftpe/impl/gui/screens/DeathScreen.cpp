#include <gui/screens/DeathScreen.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>

DeathScreen::DeathScreen() {
	this->respawnButton = 0;
	this->quitButton = 0;
	this->field_5C = 0;
	this->tickCounter = 0;
}

DeathScreen::~DeathScreen() {
	if(this->respawnButton) delete this->respawnButton;
	if(this->quitButton) delete this->quitButton;
}
void DeathScreen::render(int32_t a2, int32_t a3, float a4) {
	this->fillGradient(0, 0, this->width, this->height, 0x60500000, 0xA0803030);
	glPushMatrix();
	glScalef(2.0, 2.0, 2.0);
	this->drawCenteredString(this->font, "You died!", this->width / 4, this->height / 8, 0xFFFFFF);
	glPopMatrix();
	if(this->tickCounter > 29) {
		Screen::render(a2, a3, a4);
	}
}
void DeathScreen::init() {
	this->respawnButton = new Touch::TButton(1, "Respawn!", 0);
	this->quitButton = new Touch::TButton(2, "Main menu", 0);
	this->respawnButton->init(this->minecraft);
	this->quitButton->init(this->minecraft);
	this->buttons.push_back(this->respawnButton);
	this->buttons.push_back(this->quitButton);
	this->field_2C.push_back(this->respawnButton);
	this->field_2C.push_back(this->quitButton);
}
void DeathScreen::setupPositions() {
	int32_t v2; // r3
	int32_t v4; // r3

	v2 = this->width / 4;
	this->quitButton->width = v2;
	this->respawnButton->width = v2;
	v4 = this->height / 2;
	this->quitButton->posY = v4;
	this->respawnButton->posY = v4;
	this->respawnButton->posX = this->width / 2 - this->respawnButton->width - 10;
	this->quitButton->posX = this->width / 2 + 10;
}
void DeathScreen::tick() {
	++this->tickCounter;
}
bool_t DeathScreen::renderGameBehind() {
	return 1;
}
void DeathScreen::buttonClicked(Button* a2) {
	if(this->tickCounter > 29) {
		if(a2 == this->respawnButton) {
			this->minecraft->player->respawn();
			this->minecraft->setScreen(0);
		}
		if(a2 == this->quitButton) {
			this->minecraft->leaveGame(0, 1);
		}
	}
}
