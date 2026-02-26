#pragma once
#include <_types.h>

struct Timer{
	float ticksPerSecond;
	int32_t ticks;
	float field_8;
	float timeScale;
	float passedTime;
	float lastTime;
	int32_t lastMs;
	int32_t lastMsSysTime;
	float adjustTime;

	void advanceTime(void);
};
