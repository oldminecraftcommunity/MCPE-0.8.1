#pragma once
#include <_types.h>
#include <util/area/IArea.hpp>

struct RectangleArea : IArea{
	float minX, maxX, minY, maxY;

	RectangleArea(int8_t field_4, float minX, float minY, float maxX, float maxY);

	virtual float centerX();
	virtual float centerY();
	virtual bool_t isInside(float x, float y);
};
