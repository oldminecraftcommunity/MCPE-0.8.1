#pragma once
#include <_types.h>

struct IntRectangle{
	int32_t minX, minY;
	int32_t width, height;

	IntRectangle(int minX, int minY, int width, int height) : minX(minX), minY(minY), width(width), height(height) {
	}
	//TODO might have default constructor that calls IntRectangle(0, 0, 1, 1)
};
