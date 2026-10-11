#include <gui/screens/Touch_TouchDeleteWorldScreen.hpp>
#include <Minecraft.hpp>
#include <level/storage/LevelStorageSource.hpp>
#include <gui/screens/PlayScreen.hpp>

Touch::TouchDeleteWorldScreen::TouchDeleteWorldScreen(const LevelSummary& a2)	: ConfirmScreen(0, "Are you sure you want to delete this world?", std::string() + "'" + a2.levelName + "' will be lost forever!", "Delete", "Cancel", 0), levelSummary(a2) {
	this->field_44 = 1;
}


void Touch::TouchDeleteWorldScreen::postResult(bool_t a2) {
	if(a2) {
		this->minecraft->getLevelSource()->deleteLevel(this->levelSummary.levelDir);
	}
	this->minecraft->setScreen(new PlayScreen(1));
}
