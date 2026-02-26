#include <gui/screens/Touch_PromotionStartMenuScreen.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/ImageWithBackground.hpp>
#include <Minecraft.hpp>
#include <level/LevelSettings.hpp>
#include <gui/screens/ProgressScreen.hpp>

Touch::PromotionStartMenuScreen::~PromotionStartMenuScreen() {
}
void Touch::PromotionStartMenuScreen::init() {
	Touch::StartMenuScreen::init();
	this->playButton2 = &this->playButton;
	this->realmsButton2 = &this->playOnRealmsButton;
	this->playButton.maybeTextOnButton = "Creative";
	this->realmsButton2->maybeTextOnButton = "Survival";
	this->settingsButtonMaybe->setActiveAndVisibility(0, 0);
}
void Touch::PromotionStartMenuScreen::buttonClicked(Button* a2) {
	if(a2 == this->playButton2) {
		this->minecraft->selectLevel("creative", "creative", {0, -1});
		this->minecraft->setScreen(new ProgressScreen());
	} else if(a2 == this->realmsButton2) {
		this->minecraft->selectLevel("survival", "survival", {0, -1});
		this->minecraft->setScreen(new ProgressScreen());
	} else {
		Touch::StartMenuScreen::buttonClicked(a2);
	}
}
