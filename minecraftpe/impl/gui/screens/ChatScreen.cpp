#include <gui/screens/ChatScreen.hpp>
#include <Minecraft.hpp>
#include <cpputils.hpp>
#include <entity/LocalPlayer.hpp>
#include <gui/buttons/BlankButton.hpp>
#include <gui/buttons/Button.hpp>
#include <gui/buttons/ImageWithBackground.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/MessagePacket.hpp>
#include <rendering/Font.hpp>
#include <util/Util.hpp>

ChatScreen::ChatScreen()
	: Screen() {
	this->field_54 = "";
	this->keyboardVisible = 0;
	this->field_59 = 0;
	this->closeButton = 0;
	this->field_60 = 0;
	this->field_64 = 0;
	this->sendChatMessageButton = 0;
}
void ChatScreen::closeWindow() {
	this->minecraft->platform()->hideKeyboard();
	this->minecraft->setScreen(0);
}
void ChatScreen::drawChatMessages(int32_t a2) {
	int32_t v20 = a2;
	for(auto& msg: this->chatMessages) {
		Util::stringSplit(msg.field_10, this->width, this->font->charLength, [&v20](const std::string&, float) {
			v20 -= 9;
		});

		if(msg.field_8[0] == '/') {
			this->font->drawWordWrap(msg.field_10, 2.0, v20, this->width, Color4::GREY.toARGB(), 1, 0);
		} else {
			this->font->drawWordWrap(msg.field_10, 2.0, v20, this->width, Color4::WHITE.toARGB(), 1, 0);
		}
	}
}
bool_t ChatScreen::guiMessagesUpdated() {
	int32_t sz = this->chatMessages.size();
	if(sz != this->minecraft->gui.chatMessages.size()) {
		return 1;
	}
	for(int32_t i = 0; i != sz; ++i) {
		if(!(this->minecraft->gui.chatMessages[i].field_10 == this->chatMessages[i].field_10)) {
			return 1;
		}
	}
	return 0;
}
void ChatScreen::sendChatMessage() {
	if(this->field_54.size()) {
		MessagePacket v7(this->field_54, this->minecraft->player->username);
		this->minecraft->rakNetInstance->send(v7);
		if(!this->minecraft->isOnlineClient()) {
			this->minecraft->gui.addMessage(this->minecraft->player->username, this->field_54, 200);
		}
		this->field_78.emplace_back(this->field_54);
		this->field_84 = this->field_78.size();
		this->field_54 = "";
		this->minecraft->platform()->updateTextBoxText(this->field_54);
	}
}
void ChatScreen::updateGuiMessages() {
	this->chatMessages = this->minecraft->gui.chatMessages;
}
void ChatScreen::updateKeyboardVisibility() {
	if(this->keyboardVisible) {
		this->minecraft->platform()->showKeyboard(&this->field_54, 160, 0);
		this->updateToggleKeyboardButton();
		this->sendChatMessageButton->setActiveAndVisibility(1, 1);
		this->field_60->active = 0;
	} else {
		this->minecraft->platform()->hideKeyboard();
		this->updateToggleKeyboardButton();
		this->sendChatMessageButton->setActiveAndVisibility(0, 0);
		this->field_60->active = 1;
	}
}
void ChatScreen::updateToggleKeyboardButton() {
	ImageDef v12;
	v12.field_0 = "gui/spritesheet.png";
	v12.field_14 = 36;
	int32_t v5;
	if(this->keyboardVisible) {
		v5 = 9;
	} else {
		v5 = 0;
	}
	v12.field_24 = 1;
	v12.field_18 = v5;
	float v6 = 13.0;
	if(this->keyboardVisible) {
		v6 = 12.0;
	}
	v12.width = v6;
	float v7 = 8.0;
	if(!this->keyboardVisible) v7 = 11;
	v12.height = v7;
	v12.field_1C = (int32_t)v6;
	v12.field_20 = (int32_t)v7;
	this->field_64->setImageDef(v12, 0);
	int32_t height = this->height;
	int32_t v11;
	if(this->keyboardVisible) {
		v11 = height / 2 - this->field_64->height;
	} else {
		v11 = height - this->field_64->height;
	}
	this->field_64->posY = v11;
}

ChatScreen::~ChatScreen() {
	safeRemove<Button>(this->closeButton);
	safeRemove<Button>(this->field_60);
	safeRemove<ImageWithBackground>(this->field_64);
	safeRemove<ImageWithBackground>(this->sendChatMessageButton);
}
void ChatScreen::render(int32_t a2, int32_t a3, float a4) {
	int32_t height; // r6
	int32_t v9;		// kr00_4
	int32_t v10;	// r5
	int32_t v11;	// r0
	int32_t v12;	// r7
	int32_t v13;	// r6

	this->renderBackground(0);
	height = this->height;
	if(this->keyboardVisible) {
		v9 = this->height;
		height /= 2;
		v10 = this->width - this->field_64->width - this->sendChatMessageButton->width;
	} else {
		v10 = this->width - this->field_64->width;
	}
	v11 = this->font->height(this->field_54, v10 - 4) + 4;
	if(v11 < this->field_64->height) {
		v12 = this->field_64->height;
	} else {
		v12 = v11;
	}
	v13 = height - v12;
	this->drawChatMessages(v13);
	Screen::render(a2, a3, a4);
	this->field_60->posX = 0;
	this->field_60->posY = this->height - v12;
	this->field_60->width = v10;
	this->field_60->height = v12;
	this->fill(0, v13, v10, this->height, -16777216);
	{
		std::string ss = this->field_54;
		if(this->keyboardVisible) {
			ss += '_';
		}
		this->font->drawWordWrap(ss, 2.0, (float)v13 + 2.0, (float)v10 - 4.0, -1, 1, 0);
	}
}
void ChatScreen::init() {
	AppPlatform* v2 = this->minecraft->platform();
	v2->showDialog(2);
	v2->createUserInput();
	this->field_60 = new BlankButton(1);
	this->field_64 = new ImageWithBackground(10);
	this->field_64->init(this->minecraft->texturesPtr, 32, 32, {112, 0, 8, 67}, {120, 0, 8, 67}, 2, 2, "gui/spritesheet.png");
	this->sendChatMessageButton = new ImageWithBackground(2);
	this->sendChatMessageButton->init(this->minecraft->texturesPtr, 32, 32, {112, 0, 8, 67}, {120, 0, 8, 67}, 2, 2, "gui/spritesheet.png");
	ImageDef v27;
	v27.field_0 = "gui/spritesheet.png";
	v27.field_24 = 1;
	v27.width = 12.0;
	v27.height = 12.0;
	v27.field_14 = 48;
	v27.field_18 = 4;
	v27.field_1C = 12;
	v27.field_20 = 12;
	this->sendChatMessageButton->setImageDef(v27, 0);
	this->closeButton = new Touch::TButton(2, "Back", 0);
	this->closeButton->width = 38;
	this->closeButton->height = 18;
	((Touch::TButton*)this->closeButton)->init(this->minecraft);
	this->buttons.push_back(this->closeButton);
	this->buttons.push_back(this->field_60);
	this->buttons.emplace_back(this->field_64);

	this->updateKeyboardVisibility();
	this->field_84 = 0;
}
void ChatScreen::setupPositions() {
	this->closeButton->posX = this->width - this->closeButton->width - 4;
	this->closeButton->posY = 8;
	this->field_64->width = 20;
	this->field_64->height = 20;
	this->field_64->posX = this->width - this->field_64->width;
	this->sendChatMessageButton->width = 0;
	this->sendChatMessageButton->height = 20;
	this->sendChatMessageButton->posX = this->field_64->posX;
	this->sendChatMessageButton->posX = this->field_64->posX - this->sendChatMessageButton->width;
	this->sendChatMessageButton->posY = this->height / 2 - this->sendChatMessageButton->height;
	this->updateToggleKeyboardButton();
	this->field_64->setSize((float)this->field_64->width, (float)this->field_64->height);
	this->sendChatMessageButton->setSize((float)this->sendChatMessageButton->width, (float)this->sendChatMessageButton->height);
	this->minecraft->gui.field_A94 = 1;
}
bool_t ChatScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		if(this->keyboardVisible) {
			this->keyboardVisible = 0;
			this->updateKeyboardVisibility();
		} else {
			this->closeWindow();
		}
	}
	return 1;
}
void ChatScreen::tick() {
	Screen::tick();
	if(this->guiMessagesUpdated()) {
		this->updateGuiMessages();
	}
}
void ChatScreen::removed() {
	this->minecraft->gui.field_A94 = 0;
	this->keyboardVisible = 0;
	this->updateKeyboardVisibility();
}
bool_t ChatScreen::renderGameBehind() {
	return 1;
}
bool_t ChatScreen::isPauseScreen() {
	return 0;
}
bool_t ChatScreen::isErrorScreen() {
	return 0;
}
bool_t ChatScreen::isInGameScreen() {
	return 1;
}
bool_t ChatScreen::closeOnPlayerHurt() {
	return 1;
}
void ChatScreen::setTextboxText(const std::string& a2) {
	this->field_54 = a2;
}
void ChatScreen::buttonClicked(Button* a2) {
	if(a2 == this->closeButton) {
		this->closeWindow();
	} else if(a2 == this->field_60 || a2 == (Button*)this->field_64) {
		this->keyboardVisible ^= 1u;
		this->updateKeyboardVisibility();
	} else if(a2 == (Button*)this->sendChatMessageButton) {
		this->sendChatMessage();
	}
}
void ChatScreen::keyPressed(int32_t a2) {
	int32_t v7, sz, v9, v11;
	switch(a2) {
		case 8:
			if(!this->field_54.size()) {
				return;
			}
			this->field_54 = Util::utf8substring(this->field_54, 0, Util::utf8len(this->field_54) - 1);
			goto LABEL_17;
		case 13:
			this->sendChatMessage();
			return;
		case 38:
			v7 = (this->field_84 - 1);
			sz = this->field_78.size();
			v9 = sz - 1;
			if(v9 >= v7) {
				v9 = v7;
			}
			this->field_84 = v9 & ~(v9 >> 31);
			goto LABEL_15;
		case 40:
			v11 = this->field_84 + 1;
			sz = this->field_78.size();
			if(sz < v11) {
				v11 = this->field_78.size();
			}
			this->field_84 = v11 & ~(v11 >> 31);
			if(this->field_84 == sz) {
				this->field_54 = "";
LABEL_17:
				this->minecraft->platform()->updateTextBoxText(this->field_54);
				return;
			}
LABEL_15:
			if(!sz) {
				return;
			}
			this->field_54 = this->field_78[this->field_84];
			goto LABEL_17;
	}
	Screen::keyPressed(a2);
}
void ChatScreen::keyboardNewChar(const std::string& a2, bool_t a3) {
	std::string v8(this->field_54);
	if(this->field_59) {
		v8 = Util::utf8substring(v8, 0, Util::utf8len(v8) - 1);
	}
	v8 += a2;
	this->field_59 = a3;
	if(Util::utf8len(v8) <= 160) {
		this->field_54 = v8;
	}
}
