#pragma once
#include <_types.h>

struct TextureUVCoordinateSet{
	float minX, minY, maxX, maxY;
	float width, height;

	TextureUVCoordinateSet(float minX, float minY, float maxX, float maxY, float width, float height);
	TextureUVCoordinateSet();
	static TextureUVCoordinateSet fromOldSystem(int32_t);
};
