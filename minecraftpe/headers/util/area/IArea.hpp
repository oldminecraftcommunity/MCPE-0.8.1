#pragma once
#include <_types.h>

struct IArea{
	int8_t field_4, field_5, field_6, field_7;

	virtual ~IArea();
	virtual bool_t isInside(float x, float y) = 0;
};
