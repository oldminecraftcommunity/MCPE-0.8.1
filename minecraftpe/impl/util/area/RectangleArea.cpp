#include <util/area/RectangleArea.hpp>

RectangleArea::RectangleArea(int8_t field_4, float minX, float minY, float maxX, float maxY) {
	this->field_4 = field_4;
	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
}

bool_t RectangleArea::isInside(float x, float y){
	return x >= this->minX && x <= this->maxX && y >= this->minY && y <= this->maxY;
}

float RectangleArea::centerX(){
	return this->minX + (this->maxX-this->minX)*0.5f;
}

float RectangleArea::centerY(){
	return this->minY + (this->maxY-this->minY)*0.5f;
}
