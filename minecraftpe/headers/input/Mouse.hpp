#pragma once
#include <input/MouseDevice.hpp>

struct Mouse{
	static MouseDevice _instance;

	static void feed(int8_t, int8_t, int16_t, int16_t);
	static void feed(int8_t, int8_t, int16_t, int16_t, int16_t, int16_t);
	static int32_t getButtonState(int32_t);
	static int16_t getDX();
	static int16_t getDY();
	static MouseAction* getEvent();
	static int32_t getEventButton();
	static bool_t getEventButtonState();
	static int16_t getX();
	static int16_t getY();
	static bool_t isButtonDown(int32_t);
	static bool_t next();
	static void reset();
	static void reset2();
	static void rewind();
};
