#include <gui/screens/ConfirmScreen.hpp>
#include <gui/buttons/Touch_TButton.hpp>


ConfirmScreen::ConfirmScreen(Screen* a2, const std::string& a3, const std::string& a4, int32_t a5) {
	this->parentScreen = a2;
	this->confirmId = a5;
	this->questionText = a3;
	this->infoText = a4;
	this->confirmButtonText = "Ok";
	this->cancelButtonText = "Cancel";
	this->confirmButton = 0;
	this->cancelButton = 0;
}
ConfirmScreen::ConfirmScreen(Screen* a2, const std::string& a3, const std::string& a4, const std::string& a5, const std::string& a6, int32_t a7) {
	this->parentScreen = a2;
	this->confirmId = a7;
	this->questionText = a3;
	this->infoText = a4;
	this->confirmButtonText = a5;
	this->cancelButtonText = a6;
}

ConfirmScreen::~ConfirmScreen() {
	if(this->confirmButton) delete this->confirmButton;
	if(this->cancelButton) delete this->cancelButton;
}
void ConfirmScreen::render(int32_t a2, int32_t a3, float a4) {
	this->renderDirtBackground(0);
	this->drawCenteredString(this->font, this->questionText, this->width / 2, 50, 0xFFFFFF);
	this->drawCenteredString(this->font, this->infoText, this->width / 2, 70, 0xFFFFFF);
	Screen::render(a2, a3, a4);
}
void ConfirmScreen::init() {
	this->confirmButton = new Touch::TButton(0, 0, 0, this->confirmButtonText, 0);
	this->confirmButton->init(this->minecraft);
	this->cancelButton = new Touch::TButton(1, 0, 0, this->cancelButtonText, 0);
	this->cancelButton->init(this->minecraft);

	this->buttons.push_back(this->confirmButton);
	this->buttons.push_back(this->cancelButton);
	this->field_2C.push_back(this->confirmButton);
	this->field_2C.push_back(this->cancelButton);

}
void ConfirmScreen::setupPositions() {
	Touch::TButton* confirmButton; // r1
	Touch::TButton* v2; // r2

	this->confirmButton->posX = this->width / 2 - 124;
	this->confirmButton->posY = this->height / 6 + 72;
	this->cancelButton->posX = this->width / 2 + 4;
	this->cancelButton->posY = this->height / 6 + 72;
	confirmButton = this->confirmButton;
	this->cancelButton->width = 120;
	confirmButton->width = 120;
	v2 = this->confirmButton;
	this->cancelButton->height = 24;
	v2->height = 24;
}
bool_t ConfirmScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->postResult(0);
	}
	return 1;
}
void ConfirmScreen::buttonClicked(Button* a2) {
	this->postResult(a2->buttonID == 0);
}
void ConfirmScreen::postResult(bool_t a2) {
	this->parentScreen->confirmResult(a2, this->confirmId);
}
