#include <entity/TripodCamera.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>

TripodCamera::TripodCamera(Level* a2, Player* p, float x, float y, float z)
	: Mob(a2) {
	this->player = p;
	this->field_C70 = 80;
	this->field_C78 = 0;
	this->entityRenderId = TRIPOD_CAMERA;
	this->prevPitch = this->pitch = p->pitch;
	this->prevYaw = this->yaw = p->yaw;
	this->field_FC = 1;
	this->setSize(1.0, 1.5);
	this->ridingHeight = (this->entityHeight * 0.5f) - 0.25f;
	this->setPos(x, y, z);
	this->prevX = x;
	this->prevY = y;
	this->prevZ = z;
}

void TripodCamera::tick() {
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;

	this->move(this->motionX, this->motionY, this->motionZ);

	this->motionX *= 0.98f;
	this->motionY *= 0.98f;
	this->motionZ *= 0.98f;
	if(this->onGround) {
		this->motionZ *= 0.7f;
		this->motionX *= 0.7;
		this->motionY *= -0.5;
	}
	if(this->field_C78) {
		this->field_C70 -= 1;
		if(this->field_C70 == 8){
			this->level->takePicture(this, this->player);
			this->level->addParticle(PT_EXPLODE, this->posX, this->posY + 0.6f, this->posZ, 0, 0, 0, 0);
			this->level->addParticle(PT_EXPLODE, this->posX, this->posY + 0.8f, this->posZ, 0, 0, 0, 0);
			this->level->addParticle(PT_EXPLODE, this->posX, this->posY + 1.0f, this->posZ, 0, 0, 0, 0);
		}else if(this->field_C70 > 8){
			this->level->addParticle(PT_SMOKE, this->posX, this->posY + 1.0f, this->posZ, 0, 0, 0, 0);
		}else if(this->field_C70 == 0){
			this->remove();
		}
	}
}
float TripodCamera::getShadowHeightOffs() {
	return 0;
}
bool_t TripodCamera::interactPreventDefault() {
	return 1;
}
bool_t TripodCamera::interactWithPlayer(Player* a2) {
	this->field_C78 = 1;
	return 1;
}
bool_t TripodCamera::isPickable() {
	return !this->isDead;
}
bool_t TripodCamera::isPushable() {
	return 0;
}
