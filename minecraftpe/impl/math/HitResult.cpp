#include <math/HitResult.hpp>
#include <entity/Entity.hpp>

HitResult::HitResult(void) : hitType(2), entity(0), field_24(0), hitVec(0, 0, 0){

}

HitResult::HitResult(int32_t x, int32_t y, int32_t z, int32_t a5, const Vec3& a6) : hitType(0), x(x), y(y), z(z), field_10(a5), hitVec(a6), entity(0), field_24(0){

}

HitResult::HitResult(Entity* e)
	: hitType(1), entity(e), field_24(0), hitVec(e->posX, e->posY, e->posZ) {
}

HitResult::HitResult(const HitResult& vec)
	: hitVec(vec.hitVec) {
	this->hitType = vec.hitType;
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->field_10 = vec.field_10;
	this->entity = vec.entity;
	this->field_24 = vec.field_24;
}

float HitResult::distanceTo(Entity* entity) const{
	float v2 = this->hitVec.x - entity->posX;
	float v3 = this->hitVec.y - entity->posY;
	float v4 = this->hitVec.z - entity->posZ;
	return (v2 * v2) + (v3 * v3) + (v4 * v4);
}
