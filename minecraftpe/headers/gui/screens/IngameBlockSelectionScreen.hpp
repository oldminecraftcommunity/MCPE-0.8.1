#pragma once
#include <gui/Screen.hpp>
#include <util/area/RectangleArea.hpp>
#include <gui/buttons/Button.hpp>

struct IngameBlockSelectionScreen: Screen
{
	int32_t field_54, field_58, field_5C, field_60;
	int8_t field_64, field_65, field_66, field_67;
	Button armorButton;
	RectangleArea field_98;

	IngameBlockSelectionScreen();
	int32_t getSelectedSlot(int32_t, int32_t);
	int32_t getSlotHeight();
	int32_t getSlotPosX(int32_t);
	int32_t getSlotPosY(int32_t);
	bool_t isAllowed(int32_t);
	void renderDemoOverlay();
	void renderSlot(int32_t, int32_t, int32_t, float);
	void renderSlots();
	void selectSlotAndClose();

	virtual ~IngameBlockSelectionScreen();
	virtual void render(int32_t, int32_t, float);
	virtual void init();
	virtual void removed();
	virtual bool_t renderGameBehind();
	virtual void buttonClicked(Button*);
	virtual void mouseClicked(int32_t, int32_t, int32_t);
	virtual void mouseReleased(int32_t, int32_t, int32_t);
	virtual void keyPressed(int32_t);
};
