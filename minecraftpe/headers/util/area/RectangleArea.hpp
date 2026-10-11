#pragma once
#include <util/area/IArea.hpp>

struct RectangleArea : IArea{
	float minX, maxX, minY, maxY;

	RectangleArea(int8_t field_4, float minX, float minY, float maxX, float maxY) {
		this->field_4 = field_4;
		this->minX = minX;
		this->minY = minY;
		this->maxX = maxX;
		this->maxY = maxY;
	}
	virtual float centerX(){
		return this->minX + (this->maxX-this->minX)*0.5f;
	}
	virtual float centerY(){
		return this->minY + (this->maxY-this->minY)*0.5f;
	}
	virtual bool_t isInside(float x, float y){
		return x >= this->minX && x <= this->maxX && y >= this->minY && y <= this->maxY;
	}
};
