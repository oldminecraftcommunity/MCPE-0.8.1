#include <gui/screens/BaseContainerScreen.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>

BaseContainerScreen::~BaseContainerScreen() {
}
void BaseContainerScreen::init() {
	Screen::init();
	this->minecraft->player->currentContainer = this->field_50;
}
void BaseContainerScreen::tick() {
	Screen::tick();
	if(!this->minecraft->player->isAlive() || this->minecraft->player->isDead) {
		this->minecraft->player->closeContainer();
	}
}
bool_t BaseContainerScreen::closeOnPlayerHurt() {
	return 1;
}
