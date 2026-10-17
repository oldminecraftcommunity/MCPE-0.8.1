#pragma once
#include <_types.h>
#include <vector>

struct MouseAction{
	int16_t field_0;
	int16_t field_2;
	int16_t field_4;
	int16_t field_6;
	char evButton;
	char state;
	char field_A;

	MouseAction(char, char, int16_t, int16_t, char);
	MouseAction(char, char, int16_t, int16_t, int16_t, int16_t, char);
	bool_t isButton() const;
};

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
	void reset();
	uint8_t getButtonState(int32_t);
	bool_t isButtonDown(int32_t);
	bool_t wasFirstMovement();
	int16_t getX();
	int16_t getY();
	int16_t getDX();
	int16_t getDY();
	void reset2();
	bool_t next();
	void rewind(void);
	bool_t getEventButtonState();
	int32_t getEventButton();
	MouseAction* getEvent();
	void feed(char, char, int16_t, int16_t, int16_t, int16_t);
	void feed(char, char, int16_t, int16_t);
};

struct Mouse{
	static MouseDevice _instance;

	static void reset();
	static int32_t getButtonState(int32_t);
	static bool_t isButtonDown(int32_t);
	static int16_t getX();
	static int16_t getY();
	static int16_t getDX();
	static int16_t getDY();
	static void reset2();
	static bool_t next();
	static void rewind();
	static bool_t getEventButtonState();
	static int32_t getEventButton();
	static MouseAction* getEvent();
	static void feed(char, char, int16_t, int16_t, int16_t, int16_t);
	static void feed(char, char, int16_t, int16_t);
};
