#include <gui/screens/OptionsScreen.hpp>
#include <Minecraft.hpp>
#include <gui/OptionsGroup.hpp>
#include <gui/pane/OptionsPane.hpp>
#include <gui/buttons/CategoryButton.hpp>
#include <gui/screens/PauseScreen.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/Touch_THeader.hpp>
#include <gui/NinePatchFactory.hpp>
#include <util/IntRectangle.hpp>
#include <cpputils.hpp>

OptionsScreen::OptionsScreen(bool_t a2) {
	this->isInWorld = a2;
	this->headerOptions = 0;
	this->buttonBack = 0;
	this->field_5C = 0;
	this->field_7C = 0;
	this->field_80 = 0;
	this->field_84 = 0;
}

void OptionsScreen::closeScreen() {
	this->minecraft->options.save();
	if(this->isInWorld) {
		this->minecraft->setScreen(new PauseScreen(0));
	} else {
		this->minecraft->screenChooser.setScreen(START_MENU_SCREEN);
	}
}
int32_t OptionsScreen::createCategoryButton(int32_t a2, int32_t a3, struct ImageDef& a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8) {
	CategoryButton* v12 = new CategoryButton(a2, this->field_7C, this->field_80, (Button**)&this->field_5C);
	a4.field_24 = 1;
	a4.field_14 = a5;
	a4.field_18 = a6;
	a4.field_1C = 28;
	a4.field_20 = 28;
	v12->posX = a7;
	v12->posY = a8;
	v12->setImageDef(a4, 1);
	v12->height = a3;
	v12->width = a3;
	this->field_60.emplace_back(v12);
	return a2 + 1;
}
void OptionsScreen::createCategoryButtons(void) {
	NinePatchFactory a1(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->field_7C = a1.createSymmetrical({8, 32, 8, 8}, 2, 2, this->field_88, this->field_88);
	this->field_80 = a1.createSymmetrical({0, 32, 8, 8}, 2, 2, this->field_88, this->field_88);
	ImageDef v11;
	v11.field_0 = "gui/touchgui2.png";
	v11.width = v11.height = this->field_88;
	int32_t v7 = this->createCategoryButton(2, this->field_88, v11, 134, 0, 0, 0);
	int32_t v8 = this->createCategoryButton(v7, this->field_88, v11, 106, 0, 0, 0);
	int32_t v9 = this->createCategoryButton(v8, this->field_88, v11, 134, 28, 0, 0);
	this->createCategoryButton(v9, this->field_88, v11, 106, 28, 0, 0);
}
void OptionsScreen::generateOptionScreens(void) {
	this->optionPanes.emplace_back(new OptionsPane());
	this->optionPanes.emplace_back(new OptionsPane());
	this->optionPanes.emplace_back(new OptionsPane());
	this->optionPanes.emplace_back(new OptionsPane());

	this->optionPanes[0]->createOptionsGroup("options.group.game")->addOptionItem(&Options::Option::NAME, this->minecraft)->addOptionItem(&Options::Option::DIFFICULTY, this->minecraft)->addOptionItem(&Options::Option::THIRD_PERSON, this->minecraft)->addOptionItem(&Options::Option::SERVER_VISIBLE, this->minecraft);
	this->optionPanes[0]->createOptionsGroup("options.group.realms")->addLoginItem(this->minecraft);
	this->optionPanes[1]->createOptionsGroup("options.group.input")->addOptionItem(&Options::Option::SENSITIVITY, this->minecraft)->addOptionItem(&Options::Option::INVERT_MOUSE, this->minecraft)->addOptionItem(&Options::Option::LEFT_HANDED, this->minecraft)->addOptionItem(&Options::Option::USE_TOUCHSCREEN, this->minecraft)->addOptionItem(&Options::Option::USE_TOUCH_JOYPAD, this->minecraft)->addOptionItem(&Options::Option::PIXELS_PER_MILLIMETER, this->minecraft);
	if(this->minecraft->platform()->supportsVibration()) {
		this->optionPanes[1]->createOptionsGroup("options.group.feedback")->addOptionItem(&Options::Option::DESTROY_VIBRATION, this->minecraft);
	}
	this->optionPanes[2]->createOptionsGroup("options.group.graphics")->addOptionItem(&Options::Option::RENDER_DISTANCE, this->minecraft)->addOptionItem(&Options::Option::GRAPHICS, this->minecraft)->addOptionItem(&Options::Option::FANCY_SKIES, this->minecraft)->addOptionItem(&Options::Option::ANIMATE_TEXTURES, this->minecraft);
	this->optionPanes[2]->createOptionsGroup("options.group.graphics.experimental")->addOptionItem(&Options::Option::HIDE_GUI, this->minecraft);
	this->optionPanes[3]->createOptionsGroup("options.group.audio")->addOptionItem(&Options::Option::SOUND, this->minecraft);
}
void OptionsScreen::selectCategory(int32_t a2) {
	int32_t v2 = 0;
	for(auto&& p: this->field_60) {
		bool_t v5 = a2 == v2++;
		if(v5) {
			this->field_5C = p;
		}
		p->text = v5;
	}
	if(a2 < this->optionPanes.size()) {
		this->selectedCategory = this->optionPanes[a2];
	}
}

OptionsScreen::~OptionsScreen() {
	if(this->buttonBack) {
		delete this->buttonBack;
		this->buttonBack = 0;
	}
	if(this->headerOptions) {
		delete this->headerOptions;
		this->headerOptions = 0;
	}
	safeRemove<NinePatchLayer>(this->field_7C);
	safeRemove<NinePatchLayer>(this->field_80);
	for(auto&& p: this->field_60) {
		if(p) {
			delete p;
			p = 0;
		}
	}
	for(auto&& p: this->optionPanes) {
		if(p) {
			delete p;
			p = 0;
		}
	}
	this->field_60.clear();
	this->optionPanes.clear();
}
void OptionsScreen::render(int32_t a2, int32_t a3, float a4) {
	OptionsPane* selectedCategory; // r0
	Minecraft* minecraft; // r7
	int width; // r0
	int height; // r10
	OptionsPane* v12; // r4

	selectedCategory = this->selectedCategory;
	if(selectedCategory && selectedCategory->suppressOtherGUI()) {
		if(this->selectedCategory) {
			this->selectedCategory->topRender(this->minecraft, a2, a3);
		}
	} else {
		if(!this->isInWorld) {
			if(this->renderGameBehind()) {
				this->renderMenuBackground(a4);
			}
		}
		this->renderBackground(0);
		this->fill(0, 0, this->field_88 + 10, this->height, 0xFF958782);
		Screen::render(a2, a3, a4);
		minecraft = this->minecraft;
		width = this->width;
		height = this->height;
		v12 = this->selectedCategory;
		if(v12) {
			v12->render(minecraft, width * a2 / minecraft->field_1C, height * a3 / minecraft->field_20 - 1);
		}
	}
}
void OptionsScreen::init() {
	this->field_88 = 28;
	this->headerOptions = new Touch::THeader(0, "Options");
	this->buttonBack = new Touch::TButton(1, "Back", 0);
	this->buttonBack->width = 38;
	this->buttonBack->height = 18;
	this->buttonBack->init(this->minecraft);
	this->buttons.emplace_back(this->headerOptions);
	this->buttons.emplace_back(this->buttonBack);
	this->createCategoryButtons();
	for(auto&& i = this->field_60.begin(); i != this->field_60.end(); ++i) {
		this->buttons.emplace_back(*i);
		this->field_2C.emplace_back(*i);
	}
	this->generateOptionScreens();
}
void OptionsScreen::setupPositions() {
	int32_t v2 = this->field_60.size();
	int32_t v3 = (this->height - this->headerOptions->height - 3 - (v2 * this->field_88 + 2 * (v2 + 0x7FFFFFFF))) / 2;

	for(int32_t i = 0; i < this->field_60.size(); ++i) {
		this->field_60[i]->posY = this->headerOptions->height + 3 + v3 + 29 * i;
		this->field_60[i]->posX = 5;
	}
	this->buttonBack->posX = 4;
	this->buttonBack->posY = 4;
	this->headerOptions->posX = 0;
	this->headerOptions->posY = 0;
	this->headerOptions->width = this->width;
	this->headerOptions->height = this->buttonBack->height + 8;
	for(auto&& p: this->optionPanes) {
		if(this->field_60.size()) {
			p->posX = this->field_60[0]->width + 20;
			p->posY = this->headerOptions->height + 3;
			p->width = this->width - this->field_60[0]->width - 20;
			p->height = this->height - this->headerOptions->height - 3;
			p->setupPositions();
		}
	}
	this->selectCategory(0);
}
bool_t OptionsScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		if(!this->selectedCategory || !this->selectedCategory->suppressOtherGUI() || !this->selectedCategory->backPressed(this->minecraft, 0)) {
			this->closeScreen();
		}
	}
	return 1;
}
void OptionsScreen::tick() {
	if(this->selectedCategory) {
		this->selectedCategory->tick(this->minecraft);
	}
	Screen::tick();
}
void OptionsScreen::removed() {
}
bool_t OptionsScreen::renderGameBehind() {
	return 1;
}
void OptionsScreen::setTextboxText(const std::string& a2) {
	if(this->selectedCategory) {
		this->selectedCategory->setTextboxText(a2);
	}
}
void OptionsScreen::buttonClicked(Button* a2) {
	if(a2 == this->buttonBack) {
		this->closeScreen();
	} else {
		int32_t buttonID = a2->buttonID;
		if((uint32_t)(buttonID - 2) <= 4) {
			this->selectCategory(buttonID - this->field_60[0]->buttonID);
		}
	}
}
void OptionsScreen::mouseClicked(int32_t a2, int32_t a3, int32_t a4) {
	bool_t v8; // r0
	OptionsPane* selectedCategory; // r4

	v8 = this->selectedCategory->suppressOtherGUI();
	selectedCategory = this->selectedCategory;
	if(v8) {
		if(selectedCategory) {
			selectedCategory->focusuedMouseClicked(this->minecraft, a2, a3, a4);
		}
	} else {
		if(selectedCategory) {
			selectedCategory->mouseClicked(this->minecraft, a2, a3, a4);
		}
		Screen::mouseClicked(a2, a3, a4);
	}
}
void OptionsScreen::mouseReleased(int32_t a2, int32_t a3, int32_t a4) {
	bool_t v8; // r0
	OptionsPane* selectedCategory; // r4

	v8 = this->selectedCategory->suppressOtherGUI();
	selectedCategory = this->selectedCategory;
	if(v8) {
		if(selectedCategory) {
			selectedCategory->focusuedMouseReleased(this->minecraft, a2, a3, a4);
		}
	} else {
		if(selectedCategory) {
			selectedCategory->mouseReleased(this->minecraft, a2, a3, a4);
		}
		Screen::mouseReleased(a2, a3, a4);
	}
}
void OptionsScreen::keyPressed(int32_t a2) {
	if(this->selectedCategory) {
		this->selectedCategory->keyPressed(this->minecraft, a2);
	}
}
void OptionsScreen::keyboardNewChar(const std::string& a2, bool_t a3) {
	if(this->selectedCategory) {
		this->selectedCategory->keyboardNewChar(this->minecraft, a2, a3);
	}
}
