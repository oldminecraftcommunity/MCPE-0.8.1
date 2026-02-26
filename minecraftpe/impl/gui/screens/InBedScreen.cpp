#include <gui/screens/InBedScreen.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>

InBedScreen::InBedScreen() {
	this->leaveBedButton = 0;
}
InBedScreen::~InBedScreen() {
	if(this->leaveBedButton) delete this->leaveBedButton;
}
void InBedScreen::render(int32_t a2, int32_t a3, float a4) {
	this->renderBackground(0);
	Screen::render(a2, a3, a4);
}
void InBedScreen::init() {
	this->leaveBedButton = new Touch::TButton(1, "Leave Bed", 0);
	this->leaveBedButton->init(this->minecraft);
	this->buttons.push_back(this->leaveBedButton);
	this->field_2C.push_back(this->leaveBedButton);
}
void InBedScreen::setupPositions() {
	this->leaveBedButton->width = this->width / 3;
	this->leaveBedButton->height = (int32_t)(float)((float)this->height * 0.15);
	this->leaveBedButton->posY = this->height - (int32_t)((double)this->leaveBedButton->height * 1.5);
	this->leaveBedButton->posX = this->width / 2 - this->leaveBedButton->width / 2;
}
bool_t InBedScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->minecraft->player->stopSleepInBed(1, 1, 1);
	}
	return 1;
}
bool_t InBedScreen::renderGameBehind() {
	return 1;
}
void InBedScreen::buttonClicked(Button* a2) {
	if(this->leaveBedButton == a2) {
		this->handleBackEvent(0);
	}
}
