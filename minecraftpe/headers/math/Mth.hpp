#pragma once
#include <_types.h>
#include <util/Random.hpp>

struct Mth{
	//TODO fields
	static float _sin[65536]; //XXX initialized in NinecraftApp::init
	static Random _random; //XXX might be not inside Mth

	static float cos(float);
	static float sin(float);
	static int32_t floor(float);
	static int32_t intFloorDiv(int32_t, int32_t);
	static float wrapDegrees(float);
	static uint32_t fastRandom(void);
	static float random(void);
	static uint32_t random(int32_t);
	static float clampRotate(float, float, float);
	static float sqrt(float);
	static float atan2(float, float);
};
