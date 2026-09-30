#include <gui/screens/Touch_SelectWorldScreen.hpp>
#include <gui/elements/Touch_TouchWorldSelectionList.hpp>
#include <gui/screens/Touch_TouchDeleteWorldScreen.hpp>
#include <Minecraft.hpp>
#include <input/Mouse.hpp>
#include <util/Util.hpp>
#include <set>
#include <level/storage/LevelStorageSource.hpp>
#include <algorithm>
#include <level/LevelSettings.hpp>
#include <gui/screens/ProgressScreen.hpp>
#include <cpputils.hpp>

Touch::SelectWorldScreen::SelectWorldScreen()
	: field_54(1, "")
	, createNewButton(2, "Create new", 0)
	, selectWorldHeader(0, "Select world")
	, backButton(3, "Back", 0)
	, field_168(4, "") {
	this->selectionList = 0;
	this->field_1A9 = 0;
	this->field_1AC = 0;
	this->field_54.active = 0;
	{
		ImageDef a3;
		a3.field_0 = "gui/touchgui.png";
		a3.field_24 = 1;
		a3.width = 34;
		a3.field_18 = 0;
		a3.height = 26;
		a3.field_14 = 150;
		a3.field_1C = 34;
		a3.field_20 = 26;
		this->field_54.setImageDef(a3, 1);
	}
}
std::string Touch::SelectWorldScreen::getUniqueLevelName(const std::string& a3) {
	std::set<std::string> v14;
	for(int v6 = 0; v6 < this->field_19C.size(); ++v6) {
		v14.insert(this->field_19C[v6].worldName);
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
void Touch::SelectWorldScreen::loadLevelSource(){
	this->minecraft->getLevelSource()->getLevelList(this->field_19C);
	std::sort(this->field_19C.begin(), this->field_19C.end());
	for(int i = 0; i < this->field_19C.size(); ++i) {
		LevelSummary* v9 = &this->field_19C[i];
		if(v9->worldName != LevelStorageSource::TempLevelId) {
			this->selectionList->items.push_back(*v9);
		}
	}
}

Touch::SelectWorldScreen::~SelectWorldScreen() {
	if(this->selectionList) delete this->selectionList;
}
void Touch::SelectWorldScreen::render(int32_t mx, int32_t my, float pt) {
	this->renderBackground(0);
	if(this->field_1A8) {
		this->selectionList->render(mx, my, pt);
	} else {
		this->selectionList->render((uint8_t)this->field_1A8, (uint8_t)this->field_1A8, pt);
		this->field_1A8 = Mouse::getButtonState(1) == 0;
	}
	Screen::render(mx, my, pt);
}
void Touch::SelectWorldScreen::init() {
	this->selectionList = new Touch::TouchWorldSelectionList(this->minecraft, this->width, this->height);
	this->loadLevelSource();
	this->selectionList->commit();
	this->backButton.init(this->minecraft);
	this->createNewButton.init(this->minecraft);
	this->buttons.push_back(&this->field_54);
	this->buttons.push_back(&this->createNewButton);
	this->buttons.push_back(&this->backButton);
	this->buttons.push_back(&this->selectWorldHeader);
	this->field_1A8 = Mouse::getButtonState(1) == 0;
	this->field_2C.push_back(&this->field_168);
	this->field_2C.push_back(&this->field_54);
	this->field_2C.push_back(&this->createNewButton);
	this->field_2C.push_back(&this->backButton);
}
void Touch::SelectWorldScreen::setupPositions(){
	int32_t width, v2, v3, v4, v5, v6, height;
	width = this->field_54.width;
	this->field_54.posY = this->height - 30;
	v2 = this->width;
	this->createNewButton.posY = 0;
	this->backButton.posY = 0;
	this->selectWorldHeader.posY = 0;
	this->backButton.posX = 0;
	v3 = this->backButton.width;
	this->field_54.posX = (v2 - width) / 2;
	v4 = this->createNewButton.width;
	v5 = v2 - v4;
	this->selectWorldHeader.posX = v3;
	v6 = v3 + v4;
	height = this->createNewButton.height;
	this->createNewButton.posX = v5;
	this->selectWorldHeader.width = v2 - v6;
	this->selectWorldHeader.height = height;
}
bool_t Touch::SelectWorldScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->minecraft->cancelLocateMultiplayer();
		this->minecraft->screenChooser.setScreen(ScreenId::START_MENU_SCREEN);
	}
	return 1;
}

void Touch::SelectWorldScreen::tick(){
	if(this->field_1AC == 1) {
		int32_t v3 = this->minecraft->platform()->getUserInputStatus();
		if(v3 >= 0) {
			if(v3 == 1) {
				int32_t v4 = 0;
				std::vector<std::string> userInput = this->minecraft->platform()->getUserInput();
				std::string dest = Util::stringTrim(userInput[0]);
				std::string v21 = dest;
				do {
					++v4;
				} while(v4 != 15);
				if(v21.length() == 0) v21 = "no_name";
				v21 = this->getUniqueLevelName(v21);
				int epoch = getEpochTimeS();
				if(userInput.size() > 1) {
					std::string v24 = Util::stringTrim(userInput[1]);
					if(v24.size() != 0) {
						int v23;
						if(sscanf(v24.c_str(), "%d", &v23) <= 0) {
							epoch = Util::hashCode(v24);
						} else {
							epoch = v23;
						}
					}
				}
				int gm;
				if(userInput.size() <= 2 || userInput[2].compare("survival") != 0) {
					gm = 1;
				} else {
					gm = 0;
				}
				this->minecraft->selectLevel(v21, dest, LevelSettings{epoch, gm});
				this->minecraft->hostMultiplayer(19132);
				this->minecraft->setScreen(new ProgressScreen());
				this->field_1A9 = 1;
			}
			this->field_1AC = 0;
			this->selectionList->field_9C = 0;
			this->selectionList->field_B8 = -1;
		}
		this->selectionList->field_9C = 0;
	}else{
		this->selectionList->tick();
		if(this->selectionList->field_9C) {
			if(this->selectionList->field_B8 != this->selectionList->items.size()) {
				this->minecraft->selectLevel(this->selectionList->field_A0.worldName, this->selectionList->field_A0.field_4, LevelSettings{-1, -1});
				this->minecraft->hostMultiplayer(19132);
				this->minecraft->setScreen(new ProgressScreen());
				this->field_1A9 = 1;
				return;
			}
			this->selectionList->field_9C = 0;
			this->minecraft->platform()->createUserInput(1);
			this->field_1AC = 1;
		}
		LevelSummary v26;
		if(this->isIndexValid(this->selectionList->selectedItem)) {
			v26 = this->selectionList->items[this->selectionList->selectedItem];
		}
		this->field_54.active = this->isIndexValid(this->selectionList->selectedItem);
	}
}
bool_t Touch::SelectWorldScreen::isInGameScreen() {
	return 1;
}
void Touch::SelectWorldScreen::buttonClicked(Button* a2) {
	if(a2->buttonID == this->createNewButton.buttonID && !this->field_1AC && !this->field_1A9) {
		this->minecraft->platform()->createUserInput(1);
		this->field_1AC = 1;
	}
	if(a2->buttonID == this->field_54.buttonID) {
		if(this->isIndexValid(this->selectionList->selectedItem)) {
			this->minecraft->setScreen(new Touch::TouchDeleteWorldScreen(this->selectionList->items[this->selectionList->selectedItem]));
		}
	}
	if(a2->buttonID == this->backButton.buttonID) {
		this->minecraft->cancelLocateMultiplayer();
		this->minecraft->screenChooser.setScreen(ScreenId::START_MENU_SCREEN);
	}
	if(a2->buttonID == this->field_168.buttonID) {
		int32_t v9 = this->selectionList->getItemAtPosition(this->width / 2, this->height / 2);
		this->selectionList->selectItem(v9, 0);
	}
}
void Touch::SelectWorldScreen::keyPressed(int32_t a2) {
	if(this->field_168.text) {
		if(a2 == this->minecraft->options.keyLeft.keyCode) {
			this->selectionList->stepLeft();
		}
		if(a2 == this->minecraft->options.keyRight.keyCode) {
			this->selectionList->stepRight();
		}
	}
	Screen::keyPressed(a2);
}
bool_t Touch::SelectWorldScreen::isIndexValid(int32_t a2) {
	if(this->selectionList) {
		return a2 >= 0 && a2 < this->selectionList->getNumberOfItems() - 1;
	}
	return 0;
}
