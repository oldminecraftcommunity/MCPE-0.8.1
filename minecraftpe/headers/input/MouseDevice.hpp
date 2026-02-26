#pragma once
#include <_types.h>
#include <vector>
#include <input/MouseAction.hpp>

struct MouseDevice{
	int32_t eventId;
	int16_t mouseX, mouseY;
	int16_t hasDX, hasDY;
	int16_t prevMouseX, prevMouseY;
	bool_t buttonStates[2];
	int8_t field_12, field_13;
	std::vector<MouseAction> mouseEvents;
	int32_t firstMovement;

	MouseDevice();
	void feed(int8_t, int8_t, int16_t, int16_t);
	void feed(int8_t, int8_t, int16_t, int16_t, int16_t, int16_t);
	bool_t getButtonState(int32_t);
	int16_t getDX();
	int16_t getDY();
	MouseAction* getEvent();
	int32_t getEventButton();
	bool_t getEventButtonState();
	int16_t getX();
	int16_t getY();
	bool_t isButtonDown(int32_t);
	bool_t next();
	void reset();
	void reset2();
	void rewind(void);
	bool_t wasFirstMovement();
	//~MouseDevice() -> vec destructor -> not needed?
};
