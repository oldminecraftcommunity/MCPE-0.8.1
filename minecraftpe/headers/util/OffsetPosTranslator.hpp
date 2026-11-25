#pragma once
#include <util/IPosTranslator.hpp>

struct OffsetPosTranslator: IPosTranslator
{
	float x, y, z;
	OffsetPosTranslator() {
		this->x = this->y = this->z = 0;
	}


	virtual void to(float& x, float& y, float& z) {
		x += this->x;
		y += this->y;
		z += this->z;
	}
	virtual void to(int32_t& x, int32_t& y, int32_t& z){
		x += (int32_t)this->x;
		y += (int32_t)this->y;
		z += (int32_t)this->z;
	}
	virtual void from(float& x, float& y, float& z){
		x -= this->x;
		y -= this->y;
		z -= this->z;
	}
	virtual void from(int32_t& x, int32_t& y, int32_t& z){
		x -= (int32_t)this->x;
		y -= (int32_t)this->y;
		z -= (int32_t)this->z;
	}

	virtual ~OffsetPosTranslator() {
	}
};
