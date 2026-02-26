#include <gui/screens/Touch_DeleteWorldScreen.hpp>
#include <Minecraft.hpp>
#include <level/storage/LevelStorageSource.hpp>
#include <gui/screens/PlayScreen.hpp>

Touch::DeleteWorldScreen::DeleteWorldScreen(const LevelSummary& a2)	: ConfirmScreen(0, "Are you sure you want to delete this world?", std::string() + "'" + a2.field_4 + "' will be lost forever!", "Delete", "Cancel", 0), levelSummary(a2) {
	this->field_44 = 1;
}

Touch::DeleteWorldScreen::~DeleteWorldScreen() {
}
void Touch::DeleteWorldScreen::postResult(bool_t a2) {
	if(a2) {
		this->minecraft->getLevelSource()->deleteLevel(this->levelSummary.field_0);
	}
	this->minecraft->setScreen(new PlayScreen(1));
}
