#pragma once
#include <gui/Screen.hpp>
#include <Minecraft.hpp>
#include <rendering/Font.hpp>
#include <gui/buttons/Touch_TButton.hpp>

struct DisconnectionScreen: Screen
{
	std::string reason;
	Touch::TButton* okButton;

	DisconnectionScreen(const std::string& a2) : Screen(), reason(a2), okButton(0){
	}

	virtual ~DisconnectionScreen() {
		if(this->okButton) delete this->okButton;
	}
	virtual void render(int32_t a2, int32_t a3, float a4) {
		this->renderDirtBackground(0);
		Screen::render(a2, a3, a4);
		int32_t v9 = this->minecraft->font->width(this->reason);
		this->minecraft->font->drawShadow(this->reason, (float)((this->width - v9) / 2), (float)(this->height / 2 - 32), -1);
	}
	virtual void init() {
		this->okButton = new Touch::TButton(1, "Ok", 0);
		this->okButton->init(this->minecraft);
		this->buttons.push_back(this->okButton);
		this->field_2C.push_back(this->okButton);
		this->okButton->width = 128;
		this->okButton->posX = (this->width - this->okButton->width) / 2;
		this->okButton->posY = this->height / 2;
	}
	virtual bool_t isInGameScreen() {
		return 0;
	}
	virtual void buttonClicked(Button* a2) {
		if(a2->buttonID == this->okButton->buttonID) {
			this->minecraft->leaveGame(0, 1);
		}
	}
};
