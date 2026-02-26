#include <entity/CameraEntity.hpp>
#include <level/Level.hpp>
CameraEntity::CameraEntity(Level* a2)
	: Mob(a2) {
	this->field_C70 = -1;
	this->moveTo(128.0, 72.0, 128.0, 0.0, 90.0);
}
CameraEntity::~CameraEntity() {
}
void CameraEntity::tick() {
	int32_t v2; // r1
	float posX; // r3
	float posY; // r3
	float posZ; // r3
	Entity* e;	// r0

	v2 = this->field_C70;
	if(v2 >= 0) {
		posX = this->posX;
		this->prevX = posX;
		this->prevPosX = posX;
		posY = this->posY;
		this->prevY = posY;
		this->prevPosY = posY;
		posZ = this->posZ;
		this->prevZ = posZ;
		this->prevPosZ = posZ;
		this->prevPitch = this->pitch;
		this->prevYaw = this->yaw;
		e = this->level->getEntity(v2);
		if(e) {
			this->setPos(e->posX, e->posY + 6.0, e->posZ);
		}
	}
}
int32_t CameraEntity::getEntityTypeId() const {
	return 0;
}
float CameraEntity::getBaseSpeed() {
	return 0.2;
}
