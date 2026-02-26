#include <gui/screens/SelectWorldScreen.hpp>
#include <Minecraft.hpp>
#include <gui/elements/WorldSelectionList.hpp>
#include <gui/screens/DeleteWorldScreen.hpp>
#include <gui/screens/ProgressScreen.hpp>
#include <input/Mouse.hpp>
#include <level/LevelSettings.hpp>
#include <rendering/Font.hpp>
#include <util/Util.hpp>
#include <utils.h>
#include <set>
#include <level/storage/LevelStorageSource.hpp>
#include <algorithm>
#include <string.h>

SelectWorldScreen::SelectWorldScreen()
	: deleteButton(1, "Delete")
	, createNewButton(2, "Create new")
	, backButton(3, "Back")
	, field_EC(4, "") {
	this->selectionList = 0;
	this->field_121 = 0;
	this->field_124 = 0;
	this->deleteButton.active = 0;
}
std::string SelectWorldScreen::getUniqueLevelName(const std::string& a3) {
	std::set<std::string> v14;
	for(int v6 = 0; v6 < this->field_50.size(); ++v6) {
		v14.insert(this->field_50[v6].field_0);
	}
	std::string ret = a3;
	while(1) {
		if(v14.find(ret) == v14.end()) {
			break;
		}
		ret += '-';
	}
	return ret;
}
void SelectWorldScreen::loadLevelSource() {
	this->minecraft->getLevelSource()->getLevelList(this->field_50);
	std::sort(this->field_50.begin(), this->field_50.end());
	for(int i = 0; i < this->field_50.size(); ++i) {
		LevelSummary* v9 = &this->field_50[i];
		if(v9->field_0 != LevelStorageSource::TempLevelId) {
			this->selectionList->field_74.emplace_back(LevelSummary(*v9));
		}
	}
}

SelectWorldScreen::~SelectWorldScreen() {
	if(this->selectionList) delete this->selectionList;
}
void SelectWorldScreen::render(int32_t a2, int32_t a3, float a4) {
	this->renderBackground(0);
	this->selectionList->setComponentSelected(this->field_EC.text);
	if(this->field_120) {
		this->selectionList->render(a2, a3, a4);
	} else {
		this->selectionList->render(0, 0, a4);
		this->field_120 = Mouse::getButtonState(1) == 0;
	}
	Screen::render(a2, a3, a4);
	this->drawCenteredString(this->minecraft->font, "Select world", this->width / 2, 8, -1);
}
void SelectWorldScreen::init() {
	this->selectionList = new WorldSelectionList(this->minecraft, this->width, this->height);
	this->loadLevelSource();
	this->selectionList->commit();
	this->buttons.emplace_back(&this->deleteButton);
	this->buttons.emplace_back(&this->createNewButton);
	this->buttons.emplace_back(&this->backButton);
	this->field_120 = Mouse::getButtonState(1) == 0;
	this->field_2C.emplace_back(&this->field_EC);
	this->field_2C.emplace_back(&this->deleteButton);
	this->field_2C.emplace_back(&this->createNewButton);
	this->field_2C.emplace_back(&this->backButton);
}
void SelectWorldScreen::setupPositions() {
	int32_t v1; // r3
	int32_t v2; // r3

	v1 = this->height - 28;
	this->createNewButton.posY = v1;
	this->backButton.posY = v1;
	this->deleteButton.posY = v1;
	this->createNewButton.width = 84;
	this->deleteButton.width = 84;
	this->backButton.width = 84;
	v2 = this->width / 2;
	this->deleteButton.posX = v2 - 130;
	this->createNewButton.posX = v2 - 42;
	this->backButton.posX = v2 + 46;
}
bool_t SelectWorldScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->minecraft->cancelLocateMultiplayer();
		this->minecraft->screenChooser.setScreen(START_MENU_SCREEN);
	}
	return 1;
}

static char_t _d6723994o15[] = {0x2F, 0xA, 0xD, 9, 0, 0xC, 0x60, 0x3F, 0x2A, 0x5C, 0x3C, 0x3E, 0x7C, 0x22, 0x3A};

void SelectWorldScreen::tick() {
	int32_t v3;							   // r0
	int32_t v4;							   // r5
	AppPlatform* v5;				   // r0
	int32_t seed;					   // r5
	int32_t v8;							   // r0
	WorldSelectionList* selectionList; // r2

	if(this->field_124 == 1) {
		v3 = this->minecraft->platform()->getUserInputStatus();
		if(v3 >= 0) {
			if(v3 == 1) {
				v4 = 0;
				v5 = this->minecraft->platform();
				std::vector<std::string> v22 = v5->getUserInput();
				std::string dest = Util::stringTrim(v22[0]);
				std::string v18 = dest;
				do {
					std::string v19(1, _d6723994o15[v4]);
					++v4;
					v18 = *Util::stringReplace(v18, v19, "", -1);
				} while(v4 != 15);
				if(v18.size() == 0) {
					v18 = "no_name";
				}
				v18 = this->getUniqueLevelName(v18);
				seed = getEpochTimeS();
				if(v22.size() > 7) {
					std::string v21 = Util::stringTrim(v22[1]);
					if(v21.size()) {
						int32_t v20;
						if(sscanf(v21.c_str(), "%d", &v20) <= 0) {
							seed = Util::hashCode(v21);
						} else {
							seed = v20;
						}
					}
				}
				if((uint32_t)v22.size() <= 0xB || (v8 = v22[2].compare("survival")) != 0) { //v22[2] -> (char*)v22 + 8
					v8 = 1;
				}
				this->minecraft->selectLevel(v18, dest, {seed, v8});
				this->minecraft->hostMultiplayer(19132);
				this->minecraft->setScreen(new ProgressScreen());
				this->field_121 = 1;
			}
			this->field_124 = 0;
		}
	} else {
		this->selectionList->tick();
		selectionList = this->selectionList;
		if(selectionList->field_98) {
			this->minecraft->selectLevel(this->selectionList->field_9C.field_0, this->selectionList->field_9C.field_4, {-1, -1});
			this->minecraft->hostMultiplayer(19132);
			this->minecraft->setScreen(new ProgressScreen());
			this->field_121 = 1;
		} else {
			LevelSummary v22;
			if(this->isIndexValid(selectionList->field_6C)) {
				v22 = this->selectionList->field_74[this->selectionList->field_6C];
			}
			this->deleteButton.active = this->isIndexValid(this->selectionList->field_6C);
		}
	}
}
bool_t SelectWorldScreen::isInGameScreen() {
	return 1;
}
void SelectWorldScreen::buttonClicked(Button* a2) {
	AppPlatform* v4;				   // r6
	WorldSelectionList* selectionList; // r5
	int32_t v9;						   // r0
	LevelSummary v10;				   // [sp+0h] [bp-30h] BYREF

	if(a2->buttonID == this->createNewButton.buttonID && !this->field_124 && !this->field_121) {
		v4 = this->minecraft->platform();
		v4->showDialog(1);
		v4->createUserInput();
		this->field_124 = 1;
	}
	if(a2->buttonID == this->deleteButton.buttonID) {
		if(this->isIndexValid(this->selectionList->field_6C)) {
			this->minecraft->setScreen(new DeleteWorldScreen(LevelSummary(this->selectionList->field_74[this->selectionList->field_6C])));
		}
	}
	if(a2->buttonID == this->backButton.buttonID) {
		this->minecraft->cancelLocateMultiplayer();
		this->minecraft->screenChooser.setScreen(START_MENU_SCREEN);
	}
	if(a2->buttonID == this->field_EC.buttonID) {
		selectionList = this->selectionList;
		v9 = selectionList->getItemAtPosition(this->width / 2, this->height / 2);
		selectionList->selectItem(v9, 0);
	}
}
void SelectWorldScreen::keyPressed(int32_t a2) {
	if(this->field_EC.text) {
		if(a2 == this->minecraft->options.keyLeft.keyCode) {
			this->selectionList->stepLeft();
		}
		if(a2 == this->minecraft->options.keyRight.keyCode) {
			this->selectionList->stepRight();
		}
	}
	this->keyPressed(a2);
}
bool_t SelectWorldScreen::isIndexValid(int32_t a2) {
	if(this->selectionList) {
		return a2 >= 0 && (a2 < this->selectionList->getNumberOfItems());
	}
	return 0;
}
