#pragma once
#include <_types.h>

struct MouseAction{
	int16_t field_0;
	int16_t field_2;
	int16_t field_4;
	int16_t field_6;
	int8_t evButton;
	int8_t state;
	int8_t field_A, field_B;

	MouseAction(int8_t, int8_t, int16_t, int16_t, int8_t);
	MouseAction(int8_t, int8_t, int16_t, int16_t, int16_t, int16_t, int8_t);
	bool_t isButton();
};
