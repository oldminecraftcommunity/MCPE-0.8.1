#include <entity/PathfinderMob.hpp>
#include <entity/path/Path.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>

PathfinderMob::PathfinderMob(Level* a2)
	: Mob(a2) {
	this->attackTarget = 0;
	this->_shouldHoldGround = 0;
	this->inPanicTicksMaybe = 0;
	this->path = 0;
}
int32_t PathfinderMob::getNoActionTime() {
	return this->noActionTime;
}
bool_t PathfinderMob::isPathFinding() {
	return this->path != 0;
}
void PathfinderMob::setPath(Path* a2) {
	if(this->path) {
		delete this->path;
	}
	this->path = a2;
}

PathfinderMob::~PathfinderMob() {
	if(this->path) delete this->path;
}
bool_t PathfinderMob::canSpawn() {
	int32_t v3; // r7
	int32_t v4; // r6
	int32_t v5; // r0

	if(Mob::canSpawn()) {
		v3 = Mth::floor(this->posX);
		v4 = Mth::floor(this->boundingBox.minY);
		v5 = Mth::floor(this->posZ);
		return this->getWalkTargetValue(v3, v4, v5) >= 0.0;
	}
	return 0;
}
void PathfinderMob::updateAi() {
	int32_t inPanicTicksMaybe; // r3
	int32_t attackTarget;	   // r7
	Entity* v5;				   // r0
	Entity* target;			   // r5
	Entity* entity;			   // r0
	int32_t v9;				   // s21
	int32_t v10;			   // r9
	int32_t v11;			   // r0
	int32_t v12;			   // r10
	int32_t v13;			   // r3
	float v15;				   // s21
	float v16;				   // s16
	float v17;				   // s16
	float v18;				   // s20
	bool_t shouldHoldGround;   // r3
	float v20;				   // s15
	float v21;				   // s15
	float v22;				   // s20
	float v23;				   // s15
	float v24;				   // s17
	float v26;				   // r7
	bool_t v27;				   // r0
	float v30;				   // s15
	float x;				   // s18
	float y;				   // s16
	float i;				   // s17

	inPanicTicksMaybe = this->inPanicTicksMaybe;
	if(inPanicTicksMaybe > 0) {
		this->inPanicTicksMaybe = inPanicTicksMaybe - 1;
	}
	attackTarget = this->attackTarget;
	this->_shouldHoldGround = this->shouldHoldGround();
	if(attackTarget) {
		entity = this->level->getEntity(attackTarget);
		target = entity;
		if(entity && entity->isAlive()) {
			this->attackTarget = target->entityId;
			v26 = target->distanceTo(this);
			v27 = this->canSee(target);
			if(v27) {
				this->checkHurtTarget(target, v26);
			} else {
				this->checkCantSeeTarget(target, v26);
			}
		} else {
			target = 0;
			this->attackTarget = 0;
		}
	} else {
		v5 = this->findAttackTarget();
		target = v5;
		if(v5) {
			this->setPath(this->level->findPath(this, v5, 16.0, 1, 0, 0, 1));
			this->attackTarget = target->entityId;
		}
	}
	if(this->_shouldHoldGround || !target || this->path && this->random.genrand_int32() % 0x14) {
		if(!this->_shouldHoldGround && (!this->path && !(this->random.genrand_int32() % 0xB4) || !(this->random.genrand_int32() % 0x78) || this->inPanicTicksMaybe > 0 && (this->inPanicTicksMaybe & 7) == 1) && this->noActionTime <= 99) {
			this->findRandomStrollLocation();
		}
	} else {
		this->setPath(this->level->findPath(this, target, 16.0, 1, 0, 0, 1));
	}
	v9 = Mth::floor(this->boundingBox.minY + 0.5);
	v10 = this->isInWater();
	v11 = this->isInLava();
	this->pitch = 0.0;
	v12 = v11;
	if(this->path && this->random.genrand_int32() % 100) {
		Vec3 v34 = this->path->currentPos(this);
		v30 = this->entityWidth + this->entityWidth;
		x = v34.x;
		y = v34.y;
		for(i = v34.z; (float)((float)((float)((float)(y - y) * (float)(y - y)) + (float)((float)(this->posX - x) * (float)(this->posX - x))) + (float)((float)(this->posZ - i) * (float)(this->posZ - i))) < (float)(v30 * v30); i = v34.z) {
			this->path->next();
			if(this->path->isDone()) {
				this->setPath(0);
				v13 = 0;
				goto LABEL_62;
			}
			v34 = this->path->currentPos(this);
			x = v34.x;
			y = v34.y;
		}
		v13 = 1;
LABEL_62:
		this->isJumping = 0;
		if(v13) {
			v15 = y - (float)v9;
			v16 = atan2((float)(i - this->posZ), (float)(x - this->posX));
			v17 = (float)((float)((float)(v16 * 180.0) / 3.1416) - 90.0) - this->yaw;
			this->moveForward = this->getSpeed();
			while(v17 < -180.0) {
				v17 = v17 + 360.0;
			}
			while(v17 >= 180.0) {
				v17 = v17 - 360.0;
			}
			if(v17 > 30.0) {
				v17 = 30.0;
			} else if(v17 < -30.0) {
				v17 = -30.0;
			}
			v18 = v17 + this->yaw;
			shouldHoldGround = this->_shouldHoldGround;
			this->yaw = v18;
			if(shouldHoldGround) {
				if(target) {
					v20 = atan2((float)(target->posZ - this->posZ), (float)(target->posX - this->posX));
					v21 = (float)((float)(v20 * 180.0) / 3.1416) - 90.0;
					v22 = v18 - v21;
					this->yaw = v21;
					v23 = this->moveForward;
					v24 = (float)((float)((float)(v22 + 90.0) * 3.1416) / 180.0);
					this->moveStrafe = -(float)(Mth::sin(v24) * this->moveForward);
					this->moveForward = Mth::cos(v24) * v23;
				}
			}
			if(v15 > 0.0) {
				this->isJumping = 1;
			}
		}
		if(target) {
			this->lookAt(target, 30.0, 30.0);
		}
		if(this->isCollidedHorizontally && !this->isPathFinding()) {
			this->isJumping = 1;
		}

		if(this->random.nextFloat() < 0.8 && (v10 || v12)) {
			this->isJumping = 1;
		}
	} else {
		Mob::updateAi();
		this->setPath(0);
	}
}
float PathfinderMob::getWalkingSpeedModifier() {
	float wsm; // r0
	float v3;  // s15

	if(this->useNewAi()) {
		return 0.7;
	}
	wsm = Mob::getWalkingSpeedModifier();
	v3 = wsm;
	if(this->inPanicTicksMaybe > 0) {
		return wsm + wsm;
	}
	return v3;
}
Entity* PathfinderMob::getAttackTarget() {
	if(this->attackTarget) {
		return this->level->getEntity(this->attackTarget);
	}
	return 0;
}
void PathfinderMob::setAttackTarget(Entity* entity) {
	if(entity) {
		this->attackTarget = entity->entityId;
	} else {
		this->attackTarget = 0;
	}
}
float PathfinderMob::getWalkTargetValue(int32_t, int32_t, int32_t) {
	return 0.0;
}
Entity* PathfinderMob::findAttackTarget() {
	return 0;
}
void PathfinderMob::checkHurtTarget(Entity*, float) {
}
void PathfinderMob::checkCantSeeTarget(Entity* a2, float a3) {
	if(a3 > 32) {
		this->attackTarget = 0;
	}
}
bool_t PathfinderMob::shouldHoldGround() {
	return 0;
}
void PathfinderMob::findRandomStrollLocation() {
	float v1;	 // s16
	int32_t v2;	 // r6
	int32_t v5;	 // r5
	int32_t v6;	 // r10
	float posX;	 // s19
	int32_t v8;	 // r1
	int32_t v9;	 // r0
	float posY;	 // s19
	int32_t v11; // r8
	int32_t v12; // r1
	int32_t v13; // r0
	float posZ;	 // s19
	int32_t v15; // r9
	int32_t v16; // r1
	int32_t v17; // r11
	float v18;	 // r0
	int32_t v20; // [sp+18h] [bp-40h]
	int32_t v21; // [sp+1Ch] [bp-3Ch]

	v1 = -99999.0;
	v2 = -1;
	v5 = 10;
	v6 = -1;
	v21 = -1;
	v20 = 0;
	do {
		posX = this->posX;
		v8 = this->random.genrand_int32() % 0xD;
		v9 = Mth::floor((float)(posX + (float)v8) - 6.0);
		posY = this->posY;
		v11 = v9;
		v12 = this->random.genrand_int32() % 7;
		v13 = Mth::floor((float)(posY + (float)v12) - 3.0);
		posZ = this->posZ;
		v15 = v13;
		v16 = this->random.genrand_int32() % 0xD;
		v17 = Mth::floor((float)(posZ + (float)v16) - 6.0);
		v18 = this->getWalkTargetValue(v11, v15, v17);
		if(v18 > v1) {
			v1 = v18;
			v2 = v17;
			v6 = v11;
			v21 = v15;
			v20 = 1;
		}
		--v5;
	} while(v5);
	if(v20) {
		this->setPath(this->level->findPath(this, v6, v21, v2, 10.0, 1, 0, 0, 1));
	}
}
