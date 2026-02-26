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
	this->ridingHeight = (this->entityHeight * 0.5) - 0.25;
	this->setPos(x, y, z);
	this->prevX = x;
	this->prevY = y;
	this->prevZ = z;
}

TripodCamera::~TripodCamera() {
}
void TripodCamera::tick() {
	float v1;		 // s15
	float motionX;	 // r1
	float posZ;		 // r3
	float v5;		 // s12
	float motionZ;	 // s13
	bool_t onGround; // r3
	float v8;		 // s14
	int32_t v9;		 // r3

	v1 = this->motionY - 0.04;
	motionX = this->motionX;
	this->prevX = this->posX;
	this->prevY = this->posY;
	posZ = this->posZ;
	this->motionY = v1;
	this->prevZ = posZ;
	this->move(motionX, v1, this->motionZ);
	v5 = this->motionX * 0.98;
	motionZ = this->motionZ;
	onGround = this->onGround;
	v8 = this->motionY * 0.98;
	this->motionX = v5;
	this->motionY = v8;
	this->motionZ = motionZ * 0.98;
	if(onGround) {
		this->motionZ = (float)(motionZ * 0.98) * 0.7;
		this->motionX = v5 * 0.7;
		this->motionY = v8 * -0.5;
	}
	if(this->field_C78) {
		v9 = this->field_C70 - 1;
		this->field_C70 = v9;
		if(v9) {
			if(v9 == 8) {
				this->level->takePicture(this, this->player);
				this->level->addParticle(PT_EXPLODE, this->posX, this->posY + 0.6, this->posZ, 0.0, 0.0, 0.0, 0);
				this->level->addParticle(PT_EXPLODE, this->posX, this->posY + 0.8, this->posZ, 0.0, 0.0, 0.0, 0);
				this->level->addParticle(PT_EXPLODE, this->posX, this->posY + 1.0, this->posZ, 0.0, 0.0, 0.0, 0);
			} else if(v9 > 8) {
				this->level->addParticle(PT_SMOKE, this->posX, this->posY + 1.0, this->posZ, 0.0, 0.0, 0.0, 0);
			}
		} else {
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
int32_t TripodCamera::getEntityTypeId() const {
	return 0;
}
float TripodCamera::getBaseSpeed() {
	return 0;
}
