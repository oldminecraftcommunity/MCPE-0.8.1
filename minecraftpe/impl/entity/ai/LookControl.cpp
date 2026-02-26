#include <entity/ai/LookControl.hpp>
#include <entity/Mob.hpp>
#include <entity/path/PathNavigation.hpp>
#include <math.h>
#include <math/Mth.hpp>

LookControl::LookControl(Mob* a2) {
	this->controlledEntity = a2;
	this->isLooking = 0;
	this->pitchRotationSpeed = 0;
	this->yawRotationSpeed = 0;
	this->lookX = this->lookY = this->lookZ = 0;
}
void LookControl::setLookAt(Entity* a2, float a3, float a4) {
	this->lookX = a2->posX;
	this->lookY = a2->isMob() ? (a2->posY + a2->getHeadHeight()) : (a2->boundingBox.minY + a2->boundingBox.maxY) * 0.5;
	this->lookZ = a2->posZ;
	this->yawRotationSpeed = a3;
	this->pitchRotationSpeed = a4;
	this->isLooking = 1;
}
void LookControl::setLookAt(float x, float y, float z, float a5, float a6) {
	this->lookZ = z;
	this->lookX = x;
	this->lookY = y;
	this->yawRotationSpeed = a5;
	this->pitchRotationSpeed = a6;
	this->isLooking = 1;
}

void LookControl::tick() {
	Mob* controlledEntity;	// r5
	float lookY;			// s22
	float posY;				// s24
	float v5;				// s16
	float v6;				// r0
	float v7;				// s17
	float v8;				// s23
	float v9;				// s18
	double v10;				// d10
	double v11;				// r0
	Mob* v12;				// r5
	float v13;				// s14
	float yawRotationSpeed; // r2
	float headYaw;			// r0
	float v16;				// s16
	float v17;				// r1
	Mob* v18;				// r0
	float i;				// s16

	this->controlledEntity->pitch = 0.0;
	controlledEntity = this->controlledEntity;
	if(this->isLooking) {
		this->isLooking = 0;
		lookY = this->lookY;
		posY = controlledEntity->posY;
		v5 = this->lookX - controlledEntity->posX;
		v6 = controlledEntity->getHeadHeight();
		v7 = this->lookZ - this->controlledEntity->posZ;
		v8 = v6;
		v9 = sqrt((float)((float)(v7 * v7) + (float)(v5 * v5)));
		v10 = atan2(v7, v5);
		v11 = atan2((float)(lookY - (float)(posY + v8)), v9);
		v12 = this->controlledEntity;
		v13 = v11 * 180.0 / 3.1416;
		v12->pitch = Mth::clampRotate(v12->pitch, -v13, this->pitchRotationSpeed);
		controlledEntity = this->controlledEntity;
		yawRotationSpeed = this->yawRotationSpeed;
		headYaw = controlledEntity->headYaw;
		v16 = v10 * 180.0 / 3.1416;
		v17 = v16 - 90.0;
	} else {
		headYaw = controlledEntity->headYaw;
		v17 = controlledEntity->field_124;
		yawRotationSpeed = 10.0;
	}
	controlledEntity->headYaw = Mth::clampRotate(headYaw, v17, yawRotationSpeed);
	v18 = this->controlledEntity;
	for(i = v18->headYaw - v18->field_124; i < -180.0; i = i + 360.0) {
		;
	}
	while(i >= 180.0) {
		i = i - 360.0;
	}

	if(!v18->getNavigation()->isDone()) {
		if(i < -75.0) {
			this->controlledEntity->headYaw = this->controlledEntity->field_124 - 75.0;
		}
		if(i > 75.0) {
			this->controlledEntity->headYaw = this->controlledEntity->field_124 + 75.0;
		}
	}
}
LookControl::~LookControl() {
}
