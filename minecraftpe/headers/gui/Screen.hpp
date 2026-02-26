#pragma once
#include <_types.h>
#include <gui/GuiComponent.hpp>
#include <network/mco/MojangConnectionStatus.hpp>
#include <network/mco/MCOEvent.hpp>
#include <vector>

extern char_t* panorama_images[];
struct Button;
struct Screen : public GuiComponent{
	int32_t width, height;
	int8_t field_C, field_D, field_E, field_F;
	struct Minecraft* minecraft;
	std::vector<Button*> buttons;
	int32_t field_20, field_24, field_28;
	std::vector<Button*> field_2C;
	std::vector<struct GuiElement*> elements;
	int32_t field_44;
	struct Font* font;
	struct Button* lastPressedButton;

	void updateTabButtonSelection();
	void init(struct Minecraft*, int32_t, int32_t);
	void setSize(int32_t w, int32_t h);

	virtual ~Screen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void setupPositions(void);
	virtual void updateEvents();
	virtual void mouseEvent(void);
	virtual void keyboardEvent();
	virtual void keyboardTextEvent();
	virtual bool_t handleBackEvent(bool_t);
	virtual void tick();
	virtual void removed();
	virtual void renderBackground(int32_t);
	virtual void renderDirtBackground(int32_t);
	virtual void renderMenuBackground(float);
	virtual bool_t renderGameBehind();
	virtual bool_t hasClippingArea(struct IntRectangle&);
	virtual bool_t isPauseScreen();
	virtual bool_t isErrorScreen();
	virtual bool_t isInGameScreen();
	virtual bool_t closeOnPlayerHurt();
	virtual void confirmResult(bool_t, int32_t);
	virtual void lostFocus();
	virtual void toGUICoordinate(int32_t& x, int32_t& y);
	virtual void feedMCOEvent(MCOEvent);
	virtual bool_t supppressedBySubWindow(); //mojang moment
	virtual void onTextBoxUpdated(int32_t);
	virtual void onMojangConnectorStatus(MojangConnectionStatus);
	virtual void setTextboxText(const std::string&);
	virtual void onInternetUpdate();
	virtual void buttonClicked(Button*);
	virtual void mouseClicked(int32_t, int32_t, int32_t);
	virtual void mouseReleased(int32_t, int32_t, int32_t);
	virtual void keyPressed(int32_t);
	virtual void keyboardNewChar(const std::string&, bool_t);
	Screen();
};
