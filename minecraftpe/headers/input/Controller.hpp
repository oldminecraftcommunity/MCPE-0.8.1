#pragma once
#include <_types.h>

struct Controller
{
	static float stickValuesX[2];
	static float stickValuesY[2];
	static bool_t isTouchedValues[2];


	static void feed(int32_t, int32_t, float, float);
	static float getTransformedX(int32_t, float, float, bool_t);
	static float getTransformedY(int32_t, float, float, bool_t);
	static float getX(int32_t);
	static float getY(int32_t);
	static bool_t isTouched(int32_t);
	static bool_t isValidStick(int32_t);
	static float linearTransform(float, float, float, bool_t);
};
