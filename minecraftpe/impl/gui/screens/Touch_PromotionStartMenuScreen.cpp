#include <gui/screens/Touch_PromotionStartMenuScreen.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/ImageWithBackground.hpp>
#include <Minecraft.hpp>
#include <level/LevelSettings.hpp>
#include <gui/screens/ProgressScreen.hpp>


void Touch::PromotionStartMenuScreen::init() {
	Touch::StartMenuScreen::init();
	this->creativeButton = &this->playButton;
	this->survivalButton = &this->playOnRealmsButton;
	this->playButton.text = "Creative";
	this->survivalButton->text = "Survival";
	this->settingsButtonMaybe->setActiveAndVisibility(0, 0);
}
void Touch::PromotionStartMenuScreen::buttonClicked(Button* a2) {
	if(a2 != this->creativeButton && a2 != this->survivalButton) {
		Touch::StartMenuScreen::buttonClicked(a2);
		return;
	}

	std::string name = a2 == this->creativeButton ? "creative" : "survival";
	this->minecraft->selectLevel(name, name, {0, -1});
	this->minecraft->setScreen(new ProgressScreen());
}
