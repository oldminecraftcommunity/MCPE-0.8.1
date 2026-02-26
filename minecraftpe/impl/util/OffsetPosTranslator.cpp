#include <util/OffsetPosTranslator.hpp>

OffsetPosTranslator::OffsetPosTranslator() {
	this->x = this->y = this->z = 0;
}

OffsetPosTranslator::~OffsetPosTranslator() {
}
void OffsetPosTranslator::to(int32_t& x, int32_t& y, int32_t& z){
	x += (int32_t)this->x;
	y += (int32_t)this->y;
	z += (int32_t)this->z;
}
void OffsetPosTranslator::to(float& x, float& y, float& z) {
	x += this->x;
	y += this->y;
	z += this->z;
}
void OffsetPosTranslator::from(int32_t& x, int32_t& y, int32_t& z){
	x -= (int32_t)this->x;
	y -= (int32_t)this->y;
	z -= (int32_t)this->z;
}
void OffsetPosTranslator::from(float& x, float& y, float& z){
	x -= this->x;
	y -= this->y;
	z -= this->z;
}
