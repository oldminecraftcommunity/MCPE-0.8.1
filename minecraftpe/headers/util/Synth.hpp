#pragma once
#include <_types.h>

struct Synth{
	void create(int32_t, int32_t, float*);
	virtual	float getValue(float, float) = 0;
	int32_t getDataSize(int32_t, int32_t);
};
