#include <entity/FlyingMob.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <tile/Tile.hpp>

FlyingMob::FlyingMob(Level* a2)
	: Mob(a2) {
}

FlyingMob::~FlyingMob() {
}
void FlyingMob::causeFallDamage(float) {
}
bool_t FlyingMob::onLadder() {
	return 0;
}
void FlyingMob::travel(float a2, float a3) {
	float motionX; // s14
	float v9;	   // s15
	int32_t v10;   // r0
	Level* level;  // r8
	int32_t v12;   // r10
	int32_t v13;   // r9
	int32_t v14;   // r0
	int32_t v15;   // r0
	float v16;	   // s15
	float v17;	   // s15
	int32_t v18;   // r0
	Level* v19;	   // r6
	int32_t v20;   // r9
	int32_t v21;   // r8
	int32_t v22;   // r0
	int32_t v23;   // r0
	float v24;	   // s16
	float posZ;	   // s13
	float v26;	   // s14
	float prevZ;   // s15
	float v28;	   // s14
	float v29;	   // s15
	float v30;	   // s15

	if(this->isInWater()) {
		this->moveRelative(a2, a3, 0.02);
		this->move(this->motionX, this->motionY, this->motionZ);
		motionX = this->motionX;
		v9 = 0.8;
LABEL_5:
		this->motionX = motionX * v9;
		this->motionY = this->motionY * v9;
		this->motionZ = this->motionZ * v9;
		goto LABEL_20;
	}
	if(this->isInLava()) {
		this->moveRelative(a2, a3, 0.02);
		this->move(this->motionX, this->motionY, this->motionZ);
		v9 = 0.5;
		motionX = this->motionX;
		goto LABEL_5;
	}
	if(this->onGround) {
		v10 = Mth::floor(this->posX);
		level = this->level;
		v12 = v10;
		v13 = Mth::floor(this->boundingBox.minY - 0.5);
		v14 = Mth::floor(this->posZ);
		v15 = level->getTile(v12, v13, v14);
		if(v15 <= 0) {
			v16 = 0.546;
		} else {
			v16 = Tile::tiles[v15]->slipperiness * 0.91;
		}
	} else {
		v16 = 0.91;
	}
	if(this->onGround) {
		v17 = 0.016277 / (float)((float)(v16 * v16) * v16);
	} else {
		v17 = 0.02;
	}
	this->moveRelative(a2, a3, v17);
	if(this->onGround) {
		v18 = Mth::floor(this->posX);
		v19 = this->level;
		v20 = v18;
		v21 = Mth::floor(this->boundingBox.minY - 0.5);
		v22 = Mth::floor(this->posZ);
		v23 = v19->getTile(v20, v21, v22);
		if(v23 <= 0) {
			v24 = 0.546;
		} else {
			v24 = Tile::tiles[v23]->slipperiness * 0.91;
		}
	} else {
		v24 = 0.91;
	}
	this->move(this->motionX, this->motionY, this->motionZ);
	this->motionX = this->motionX * v24;
	this->motionY = this->motionY * v24;
	this->motionZ = this->motionZ * v24;
LABEL_20:
	posZ = this->posZ;
	v26 = this->posX - this->prevX;
	prevZ = this->prevZ;
	this->field_168 = this->field_16C;
	v28 = sqrt((float)((float)((float)(posZ - prevZ) * (float)(posZ - prevZ)) + (float)(v26 * v26)));
	v29 = v28 * 4.0;
	if((float)(v28 * 4.0) > 1.0) {
		v29 = 1.0;
	}
	v30 = this->field_16C + (float)((float)(v29 - this->field_16C) * 0.4);
	this->field_16C = v30;
	this->field_170 = this->field_170 + v30;
}
