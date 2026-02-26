#include <entity/player/PlayerData.hpp>
#include <entity/Player.hpp>
#include <math.h>

PlayerData::PlayerData() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->motX = 0;
	this->motY = 0;
	this->motZ = 0;
}

void PlayerData::loadPlayer(Player* a2) {
	float x;	 // s15
	float y;	 // s15
	float z;	 // s15
	float motX;	 // s13
	float moyY;	 // s14
	float motZ;	 // s15
	float v10;	 // s10
	bool_t v11;	 // fzf
	bool_t v12;	 // fnf
	float v13;	 // s10
	bool_t v14;	 // cc
	bool_t v15;	 // fzf
	bool_t v16;	 // fnf
	float v17;	 // s10
	float pitch; // s15
	float yaw;	 // s15

	a2->setPos(0.0, 0.0, 0.0);
	x = this->x;
	if(this->x > 252.0) {
		x = 252.0;
	} else if(x <= 4.0) {
		x = 4.0;
	}
	a2->prevPosX = x;
	a2->prevX = x;
	a2->posX = x;
	y = this->y;
	if(y > 126.0) {
		y = 126.0;
	} else if(y <= 4.0) {
		y = 4.0;
	}
	a2->prevPosY = y;
	a2->prevY = y;
	a2->posY = y;
	z = this->z;
	if(z > 252.0) {
		z = 252.0;
	} else if(z <= 4.0) {
		z = 4.0;
	}
	a2->prevPosZ = z;
	a2->prevZ = z;
	a2->posZ = z;
	motX = this->motX;
	moyY = this->motY;
	motZ = this->motZ;
	v10 = fabsf(motX);
	v11 = v10 == 10.0;
	v12 = v10 < 10.0;
	v13 = fabsf(moyY);
	v14 = v12 || v11;
	v15 = v13 == 10.0;
	v16 = v13 < 10.0;
	v17 = fabsf(motZ);
	if(!v14) {
		motX = 0.0;
	}
	a2->motionX = motX;
	if(!v16 && !v15) {
		moyY = 0.0;
	}
	a2->motionY = moyY;
	if(v17 > 10.0) {
		motZ = 0.0;
	}
	a2->motionZ = motZ;
	pitch = this->pitch;
	if(pitch > 100000.0) {
		pitch = 100000.0;
	} else if(pitch <= -100000.0) {
		pitch = -100000.0;
	}
	a2->prevPitch = pitch;
	a2->pitch = pitch;
	yaw = this->yaw;
	if(yaw > 100000.0) {
		yaw = 100000.0;
	} else if(yaw <= -100000.0) {
		yaw = -100000.0;
	}
	a2->prevYaw = yaw;
	a2->yaw = yaw;
	a2->fallDistance = this->fallDistance;
	a2->fire = this->fire;
	a2->air = this->field_26;
	a2->onGround = this->onGround;
	a2->setPos(this->x, this->y, this->z);
}
