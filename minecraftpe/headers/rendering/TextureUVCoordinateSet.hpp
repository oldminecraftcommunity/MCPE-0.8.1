#pragma once
#include <_types.h>

struct TextureUVCoordinateSet{
	float minX, minY, maxX, maxY;
	float width, height;

	TextureUVCoordinateSet(float minX, float minY, float maxX, float maxY, float width, float height){
		this->width = width;
		this->height = height;
		this->minX = minX;
		this->minY = minY;
		this->maxX = maxX;
		this->maxY = maxY;
	}


	TextureUVCoordinateSet(){
		this->minX = 0;
		this->minY = 0;
		this->maxX = 0;
		this->maxY = 0;
	}
	static TextureUVCoordinateSet fromOldSystem(int32_t sprite) {
		int spx = sprite % 16;
		int spy = sprite / 16;
		float minX = (spx*16) / 256.0f;
		float maxX = ((spx+1)*16) / 256.0f;

		float minY = (spy*16) / 256.0f;
		float maxY = ((spy + 1)*16) / 256.0f;
		return TextureUVCoordinateSet(minX, minY, maxX, maxY, 256.0f, 256.0f);
	}
};
