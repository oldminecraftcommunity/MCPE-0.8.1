#pragma once
#include <_types.h>

struct SmoothFloat
{
	float field_0, field_4, field_8;
	SmoothFloat(); //always inlined
	float getNewDeltaValue(float, float);
};
