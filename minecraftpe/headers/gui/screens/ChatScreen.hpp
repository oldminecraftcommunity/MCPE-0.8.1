#pragma once
#include <gui/Screen.hpp>

struct GuiMessage;
struct ImageWithBackground;
struct Minecraft;
struct ChatScreen: Screen
{
	std::string field_54;
	bool_t keyboardVisible;
	int8_t field_59, field_5A, field_5B;
	Button* closeButton;
	Button* field_60;
	ImageWithBackground* field_64;
	ImageWithBackground* sendChatMessageButton;
	std::vector<GuiMessage> chatMessages;
	std::vector<std::string> field_78;
	int32_t field_84;

	ChatScreen();
	void closeWindow();
	void drawChatMessages(int32_t);
	bool_t guiMessagesUpdated();
	void sendChatMessage();
	void updateGuiMessages();
	void updateKeyboardVisibility();
	void updateToggleKeyboardButton();

	virtual ~ChatScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual void removed();
	virtual bool_t renderGameBehind();
	virtual bool_t isPauseScreen();
	virtual bool_t isErrorScreen();
	virtual bool_t isInGameScreen();
	virtual bool_t closeOnPlayerHurt();
	virtual void setTextboxText(const std::string&);
	virtual void buttonClicked(Button*);
	virtual void keyPressed(int32_t);
	virtual void keyboardNewChar(const std::string&, bool_t);
};
