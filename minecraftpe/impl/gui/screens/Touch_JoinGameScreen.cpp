#include <gui/screens/Touch_JoinGameScreen.hpp>
#include <gui/elements/Touch_AvailableGamesList.hpp>
#include <Minecraft.hpp>
#include <network/PingedCompatibleServer.hpp>
#include <gui/screens/ProgressScreen.hpp>
#include <network/RakNetInstance.hpp>
#include <rendering/Font.hpp>
#include <utils.h>

Touch::JoinGameScreen::JoinGameScreen()
	: joinGameButton(2, "Join Game")
	, backButton(3, "Back", 0)
	, field_BC(0, "") {
	this->field_F0 = 0;
	this->joinGameButton.active = 0;
}

Touch::JoinGameScreen::~JoinGameScreen() {
	if(this->field_F0) {
		delete this->field_F0;
	}
}
void Touch::JoinGameScreen::render(int32_t a2, int32_t a3, float a4) {
	int32_t v9; // r6
	RolledSelectionListV* v10; // r0
	int32_t v11; // r5
	int32_t v12; // r6
	Font* v16; // r6

	v9 = this->minecraft->platform()->isNetworkEnabled(1);
	this->renderBackground(0);
	v10 = this->field_F0;
	if ( v9 )
	{
		v10->render(a2, a3, a4);
	}
	else
	{
		v10->renderDirtBackground();
	}
	Screen::render(a2, a3, a4);
	v11 = this->field_BC.posX + this->field_BC.width / 2;
	if ( v9 )
	{
		this->drawCenteredString(this->minecraft->font, "Scanning for WiFi Games...", v11, 8, -1);
		v12 = this->minecraft->font->width("Scanning for WiFi Games...");
		this->drawCenteredString(this->minecraft->font, std::string(1, ("-\\|/")[(int32_t)(getTimeS() * 5.5) % 4]), v11 + v12 / 2 + 6, 8, -1);
	}
	else
	{
		this->drawCenteredString(this->minecraft->font, "WiFi is disabled", v11, 8, -1);
	}
}
void Touch::JoinGameScreen::init() {
	this->backButton.init(this->minecraft);
	this->buttons.emplace_back(&this->backButton);
	this->buttons.emplace_back(&this->field_BC);
	this->minecraft->rakNetInstance->clearServerList();
	this->field_F0 = new Touch::AvailableGamesList(this->minecraft, this->width, this->height);
	this->field_2C.emplace_back(&this->backButton);
}
void Touch::JoinGameScreen::setupPositions() {
	int32_t width; // r3
	int32_t v2; // r2

	this->joinGameButton.posY = 0;
	this->backButton.posY = 0;
	this->field_BC.posY = 0;
	this->backButton.posX = 0;
	width = this->backButton.width;
	v2 = this->width;
	this->field_BC.posX = width;
	this->field_BC.width = v2 - width;
}
bool_t Touch::JoinGameScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->minecraft->cancelLocateMultiplayer();
		this->minecraft->screenChooser.setScreen(START_MENU_SCREEN);
	}
	return 1;
}
void Touch::JoinGameScreen::tick() {
	printf("Touch::JoinGameScreen::tick - not implemented\n"); //TODO Touch::JoinGameScreen::tick, can be created but unused?
}
bool_t Touch::JoinGameScreen::isInGameScreen() {
	return 0;
}
void Touch::JoinGameScreen::buttonClicked(Button* a2) {
	if(a2->buttonID == this->joinGameButton.buttonID) {
		if(this->isIndexValid(this->field_F0->selectedItem)) {
			PingedCompatibleServer v6(this->field_F0->servers[this->field_F0->selectedItem]);
			this->minecraft->joinMultiplayer(v6, 0);
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
bool_t Touch::JoinGameScreen::isIndexValid(int32_t a2) {
	if(this->field_F0) {
		return (a2 >= 0 && a2 < this->field_F0->getNumberOfItems());
	}
	return 0;
}
