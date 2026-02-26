#include <gui/screens/PauseScreen.hpp>
#include <cpputils.hpp>
#include <Minecraft.hpp>
#include <level/Level.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/elements/Label.hpp>
#include <gui/PackedScrollContainer.hpp>
#include <gui/screens/OptionsScreen.hpp>
#include <entity/LocalPlayer.hpp>
#include <util/IntRectangle.hpp>
#include <network/RakNetInstance.hpp>

PauseScreen::PauseScreen(bool_t a2)
	: Screen() {
	this->field_5C = a2;
	this->field_54 = 0;
	this->tickCounter = 0;
	this->backToGameButton = 0;
	this->quitToTitleButton = 0;
	this->quitAndCopyMapButton = 0;
	this->optionsButton = 0;
	this->field_74 = 0;
}
bool_t PauseScreen::playerListChanged(std::vector<Player*>& a2) {
	int32_t sz = this->players.size();
	if(sz != a2.size()) return 1;
	for(int32_t i = 0; i != sz; ++i) {
		if(this->players[i] != a2[i]) return 1;
	}
	return 0;
}
void PauseScreen::rebuildPlayerList(std::vector<Player*>& a2) {
	//TODO check
	this->field_74->clearAll();
	for(auto& p: a2) {
		std::shared_ptr<GuiElementContainer> ptr(new GuiElementContainer(0, 1, 0, 0, 0, 15));
		int32_t v8 = 0xff777777;
		if(p->username == this->minecraft->player->username) v8 = 0xffffffff;
		std::shared_ptr<Label> ptr2(new Label(p->username, this->minecraft, v8, 0, 0, 0, 1));
		ptr->setBackground(this->minecraft, "gui/spritesheet.png", IntRectangle{0, 54, 3, 3}, 1, 1);
		ptr2->posX = 3;
		ptr2->posY = 4;
		ptr2->height = 12;
		ptr->addChild(ptr2);
		this->field_74->addChild(ptr);
	}
	this->field_74->setupPositions();
}

PauseScreen::~PauseScreen() {
	safeRemove<Button>(this->backToGameButton);
	safeRemove<Button>(this->quitToTitleButton);
	safeRemove<Button>(this->quitAndCopyMapButton);
	safeRemove<Button>(this->optionsButton);
	safeRemove<PackedScrollContainer>(this->field_74); //inlined
	safeRemove<Label>(this->gameMenuLabel); //inlined
}
void PauseScreen::render(int32_t a2, int32_t a3, float a4) {
	this->renderBackground(0);
	Screen::render(a2, a3, a4);
}
void PauseScreen::init() {
	this->backToGameButton = new Touch::TButton(1, "Back to game", 0);
	this->quitToTitleButton = new Touch::TButton(2, "Quit to title", 0);
	this->quitAndCopyMapButton = new Touch::TButton(3, "Quit and copy map", 0);
	this->optionsButton = new Touch::TButton(4, "Options", 0);
	((Touch::TButton*)this->backToGameButton)->init(this->minecraft);
	((Touch::TButton*)this->quitToTitleButton)->init(this->minecraft);
	((Touch::TButton*)this->quitAndCopyMapButton)->init(this->minecraft);
	((Touch::TButton*)this->optionsButton)->init(this->minecraft);
	this->gameMenuLabel = new Label("Game menu", this->minecraft, -1, 0, 0, 0, 1);
	this->field_74 = new PackedScrollContainer(1, 0, 1);
	this->field_74->setBackground(this->minecraft, "gui/spritesheet.png", IntRectangle{0, 53, 3, 4}, 1, 1);
	this->buttons.push_back(this->backToGameButton);
	this->buttons.push_back(this->optionsButton);
	this->buttons.push_back(this->quitToTitleButton);
	this->elements.emplace_back(this->field_74);
	this->elements.emplace_back(this->gameMenuLabel);
	if(this->minecraft->rakNetInstance) {
		this->minecraft->rakNetInstance->isServer();
	}

}
void PauseScreen::setupPositions() {
	int32_t v2; // r5
	int32_t v3; // r0
	Button* backToGameButton; // r1
	Button* quitToTitleButton; // r2
	Button* quitAndCopyMapButton; // r6
	int32_t width; // r2

	v2 = this->width / 20;
	v3 = this->height / 10;
	backToGameButton = this->backToGameButton;
	quitToTitleButton = this->quitToTitleButton;
	this->field_54 = 0;
	quitToTitleButton->width = 8 * v2;
	backToGameButton->width = 8 * v2;
	quitAndCopyMapButton = this->quitAndCopyMapButton;
	width = this->backToGameButton->width;
	this->optionsButton->width = width;
	quitAndCopyMapButton->width = width;
	this->backToGameButton->posX = v2;
	this->backToGameButton->posY = 48;
	this->optionsButton->posX = v2;
	this->optionsButton->posY = 80;
	this->quitToTitleButton->posX = v2;
	this->quitToTitleButton->posY = 112;
	this->gameMenuLabel->posX = this->backToGameButton->posX + this->backToGameButton->width / 2 - this->gameMenuLabel->width / 2;
	this->gameMenuLabel->posY = this->backToGameButton->posY - 17;
	this->quitAndCopyMapButton->posX = (this->width - this->quitAndCopyMapButton->width) / 2;
	this->quitAndCopyMapButton->posY = 144;
	this->field_74->width = 8 * v2;
	this->field_74->height = 8 * v3;
	this->field_74->posX = this->width - this->field_74->width - v2;
	this->field_74->posY = v3;
}
void PauseScreen::tick() {
	if(this->playerListChanged(this->minecraft->level->playersMaybe)) {
		this->rebuildPlayerList(this->minecraft->level->playersMaybe);
		this->players = this->minecraft->level->playersMaybe;
	}
	++this->tickCounter;
}
bool_t PauseScreen::renderGameBehind() {
	return 1;
}
void PauseScreen::buttonClicked(Button* a2) {
	if(a2->buttonID == this->backToGameButton->buttonID) {
		this->minecraft->setScreen(0);
		return;
	}
	if(a2->buttonID == this->quitToTitleButton->buttonID) {
		this->minecraft->leaveGame(0, 1);
		return;
	}
	if(a2->buttonID == this->quitAndCopyMapButton->buttonID) {
		this->minecraft->leaveGame(1, 1);
		return;
	}
	if(a2->buttonID == this->optionsButton->buttonID) {
		this->minecraft->setScreen(new OptionsScreen(1));
	}

}
