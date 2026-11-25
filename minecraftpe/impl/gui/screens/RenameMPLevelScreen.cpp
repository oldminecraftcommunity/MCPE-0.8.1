#include <gui/screens/RenameMPLevelScreen.hpp>
#include <Minecraft.hpp>
#include <level/storage/LevelStorageSource.hpp>
#include <util/Util.hpp>

static char_t _D6723994[] = {0x2F, 0xA, 0xD, 9, 0, 0xC, 0x60, 0x3F, 0x2A, 0x5C, 0x3C, 0x3E, 0x7C, 0x22, 0x3A, 0x2F};

RenameMPLevelScreen::RenameMPLevelScreen(const std::string& a2) : name(a2) {
}

void RenameMPLevelScreen::render(int32_t a2, int32_t a3, float a4) {
	this->renderBackground(0);
	int inputStatus = this->minecraft->platform()->getUserInputStatus();
	if(inputStatus >= 0) {
		if(inputStatus == 1) {
			std::vector<std::string> v14 = this->minecraft->platform()->getUserInput();
			if(v14.begin() != v14.end()) {
				std::string dest = v14[0];
				for(int v8 = 0; v8 != 15; ++v8){
					dest = *Util::stringReplace(dest, std::string(1, _D6723994[v8]), "", -1);
				}
				if(dest.size() == 0) {
					dest = "saved_world";
				}
				this->minecraft->getLevelSource()->renameLevel(this->name, dest);
			}
		}
		this->minecraft->screenChooser.setScreen(START_MENU_SCREEN);
	}
}
void RenameMPLevelScreen::init() {
	AppPlatform* v1 = this->minecraft->platform();

	v1->showDialog(4);
	v1->createUserInput();
}
