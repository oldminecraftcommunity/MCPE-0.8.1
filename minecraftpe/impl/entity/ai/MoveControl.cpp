#include <entity/ai/MoveControl.hpp>
#include <entity/Mob.hpp>
#include <entity/ai/JumpControl.hpp>
#include <math.h>

MoveControl::MoveControl(Mob* a2) {
	this->controlledEntity = a2;
	this->posX = a2->posX;
	this->posY = a2->posY;
	this->posZ = a2->posZ;
	this->speedMultiplier = 0;
	this->_hasWanted = 0;
}
float MoveControl::getSpeed() {
	return this->speedMultiplier;
}
bool_t MoveControl::hasWanted() {
	return this->_hasWanted;
}
void MoveControl::setWantedPosition(float x, float y, float z, float speed) {
	this->posX = x;
	this->posY = y;
	this->posZ = z;
	this->speedMultiplier = speed;
	this->_hasWanted = 1;
}

MoveControl::~MoveControl() {
}
void MoveControl::tick() {
	Mob* controlledEntity; // r3
	float v3;			   // s14
	int32_t v4;			   // s15
	float v5;			   // s14
	float v6;			   // s18
	float v7;			   // s16
	float v8;			   // s13
	double v9;			   // r0
	Mob* v10;			   // r6
	float yaw;			   // s19
	float v12;			   // s14
	float v13;			   // r0
	float v14;			   // s15
	Mob* v15;			   // r5
	float speedMultiplier; // s19
	float v17;			   // r0

	this->controlledEntity->setYya(0.0);
	if(this->_hasWanted) {
		this->_hasWanted = 0;
		controlledEntity = this->controlledEntity;
		v3 = controlledEntity->boundingBox.minY + 0.5;
		v4 = (int32_t)v3;
		if(v3 < (float)(int32_t)v3) {
			--v4;
		}
		v5 = this->posX - controlledEntity->posX;
		v6 = v5 * v5;
		v7 = this->posY - (float)v4;
		v8 = this->posZ - controlledEntity->posZ;
		if((float)((float)((float)(v5 * v5) + (float)(v7 * v7)) + (float)(v8 * v8)) >= 0.00000025) {
			v9 = atan2(v8, v5);
			v10 = this->controlledEntity;
			yaw = v10->yaw;
			v12 = v9 * 180.0 / 3.1416;
			v13 = fmodf((float)(v12 - 90.0) - yaw, 360.0);
			v14 = v13;
			if(v13 >= 180.0) {
				v14 = v13 - 360.0;
			}
			if(v14 < -180.0) {
				v14 = v14 + 360.0;
			}
			if(v14 > 30.0) {
				v14 = 30.0;
			} else if(v14 < -30.0) {
				v14 = -30.0;
			}
			v10->yaw = yaw + v14;
			v15 = this->controlledEntity;
			speedMultiplier = this->speedMultiplier;
			v17 = v15->getBaseSpeed();
			v15->setSpeed(speedMultiplier * v17);
			if(v7 > 0.0 && (float)(v6 + (float)(v8 * v8)) < 1.0) {
				this->controlledEntity->getJumpControl()->jump();
			}
		}
	}
}
