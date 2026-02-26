#include <gui/screens/JoinGameScreen.hpp>
#include <Minecraft.hpp>
#include <gui/elements/AvailableGamesList.hpp>
#include <gui/screens/ProgressScreen.hpp>
#include <network/PingedCompatibleServer.hpp>
#include <network/RakNetInstance.hpp>
#include <rendering/Font.hpp>
#include <utils.h>

JoinGameScreen::JoinGameScreen()
	: joinGameButton(2, "Join Game")
	, backButton(3, "Back") {
	this->availableGameList = 0;
	this->joinGameButton.active = 0;
}

JoinGameScreen::~JoinGameScreen() {
	if(this->availableGameList) delete this->availableGameList;
}
void JoinGameScreen::render(int32_t a2, int32_t a3, float a4) {
	int32_t v9; // r5
	int32_t v10; // r5
	double timeS; // r0
	Font* font; // r6

	v9 = this->minecraft->platform()->isNetworkEnabled(1);
	this->renderBackground(0);
	if(v9) {
		this->availableGameList->render(a2, a3, a4);
	}
	Screen::render(a2, a3, a4);
	if(v9) {
		this->drawCenteredString(this->minecraft->font, "Scanning for WiFi Games...", this->width / 2, 8, -1);
		v10 = this->minecraft->font->width("Scanning for WiFi Games...") / 2 + this->width / 2 + 6;
		timeS = getTimeS();
		font = this->minecraft->font;
		this->drawCenteredString(font, (&"-\\|/")[(int32_t)(timeS * 5.5) % 4], v10, 8, -1);
	} else {
		this->drawCenteredString(this->minecraft->font, "WiFi is disabled", this->width / 2, this->height / 2 - 8, -1);
	}
}
void JoinGameScreen::init() {
	this->buttons.emplace_back(&this->joinGameButton);
	this->buttons.emplace_back(&this->backButton);
	this->minecraft->rakNetInstance->clearServerList();
	this->availableGameList = new AvailableGamesList(this->minecraft, this->width, this->height);
	this->field_2C.emplace_back(&this->joinGameButton);
	this->field_2C.emplace_back(&this->backButton);
}
void JoinGameScreen::setupPositions() {
	int32_t v1; // r3
	int32_t v2; // r3

	v1 = this->height - 26;
	this->joinGameButton.posY = v1;
	this->backButton.posY = v1;
	this->joinGameButton.width = 120;
	this->backButton.width = 120;
	v2 = this->width / 2;
	this->joinGameButton.posX = v2 - 124;
	this->backButton.posX = v2 + 4;
}
bool_t JoinGameScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->minecraft->cancelLocateMultiplayer();
		this->minecraft->screenChooser.setScreen(START_MENU_SCREEN);
	}
	return 1;
}
void JoinGameScreen::tick() {
	uint32_t v2 = 0;
	std::vector<PingedCompatibleServer>* v3 = this->minecraft->rakNetInstance->getServerList();
	std::vector<PingedCompatibleServer> v14;
	while(v2 < v3->size()) {
		if(v3->at(v2).field_0.GetLength()) {
			v14.emplace_back(v3->at(v2));
		}
		++v2;
	}
	if(v14.size() == this->availableGameList->servers.size()) {
		int32_t v11 = v14.size() - 1;
		int32_t v12 = v11;
		while(v11 >= 0) {
			for(int32_t i = 0; i < v14.size(); ++i) {
				if(v14[i].field_4 == this->availableGameList->servers[v12].field_4) {
					this->availableGameList->servers[v12].field_0 = v14[i].field_0;
				}
			}
			--v11;
			--v12;
		}
	} else {
		PingedCompatibleServer v15;
		bool_t v7;
		if(this->isIndexValid(this->availableGameList->selectedItem)) {
			v7 = 1;
			v15 = this->availableGameList->servers[this->availableGameList->selectedItem];
		} else {
			v7 = 0;
		}
		this->availableGameList->selectItem(-1, 0);
		if(v7) {
			for(uint32_t j = 0;; ++j) {
				if(j >= this->availableGameList->servers.size()) break;
				if(this->availableGameList->servers[j].field_4 == v15.field_4) {
					this->availableGameList->selectItem(j, 0);
					break;
				}
			}
		}
	}
	this->joinGameButton.active = this->isIndexValid(this->availableGameList->selectedItem);
}
bool_t JoinGameScreen::isInGameScreen() {
	return 0;
}
void JoinGameScreen::buttonClicked(Button* a2) {
	if(a2->buttonID == this->joinGameButton.buttonID) {
		if(this->isIndexValid(this->availableGameList->selectedItem)) {
			this->minecraft->joinMultiplayer(PingedCompatibleServer(this->availableGameList->servers[this->availableGameList->selectedItem]), 0);
			this->joinGameButton.active = 0;
			this->backButton.active = 0;
			this->minecraft->setScreen(new ProgressScreen());
		}
	}
	if(a2->buttonID == this->backButton.buttonID) {
		this->minecraft->cancelLocateMultiplayer();
		this->minecraft->screenChooser.setScreen(START_MENU_SCREEN);
	}
}
bool_t JoinGameScreen::isIndexValid(int32_t a2) {
	if(this->availableGameList) {
		return a2 >= 0 && a2 < this->availableGameList->getNumberOfItems();
	}
	return 0;
}
