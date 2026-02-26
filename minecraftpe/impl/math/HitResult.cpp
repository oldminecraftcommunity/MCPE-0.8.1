#include <math/HitResult.hpp>
#include <entity/Entity.hpp>

HitResult::HitResult(int32_t a2, int32_t a3, int32_t a4, int32_t a5, const Vec3& a6) : hitVec(a6.x, a6.y, a6.z){
	this->field_C = a4;
	this->hitType = 0;
	this->field_10 = a5;
	this->field_4 = a2;
	this->field_8 = a3;
	this->entity = 0;
	this->field_24 = 0;
}

HitResult::HitResult(void) : hitVec(0, 0, 0){
	this->hitType = 2;
	this->entity = 0;
	this->field_24 = 0;
}

HitResult::HitResult(Entity* e)
	: hitVec(e->posX == 0 ? 0 : e->posX, e->posY == 0 ? 0 : e->posY, e->posZ == 0 ? 0 : e->posZ) {
	this->hitType = 1;
	this->entity = e;
	this->field_24 = 0;
}
HitResult::HitResult(const HitResult& vec)
	: hitVec(vec.hitVec) {
	this->hitType = vec.hitType;
	this->field_4 = vec.field_4;
	this->field_8 = vec.field_8;
	this->field_C = vec.field_C;
	this->field_10 = vec.field_10;
	this->entity = vec.entity;
	this->field_24 = vec.field_24;
}
float HitResult::distanceTo(Entity* entity) {
	float v2, v3, v4;
	v2 = this->hitVec.x - entity->posX;
	v3 = this->hitVec.y - entity->posY;
	v4 = this->hitVec.z - entity->posZ;
	return (v3 * v3) + (v2 * v2) + (v4 * v4);
}
