#include <entity/Monster.hpp>
#include <level/Level.hpp>
#include <level/LightLayer.hpp>

Monster::Monster(Level* a2)
	: PathfinderMob(a2) {
	this->attackDamage = 2;
	this->lastHurtByMaybe = 0;
	this->entityRenderId = HUMANOID;
}
bool_t Monster::isDarkEnoughToSpawn() {
	float posX; // s15
	int32_t v4; // r7
	bool_t v5;	// fnf
	float minY; // s15
	int32_t v7; // r6
	bool_t v8;	// fnf
	float posZ; // s15
	int32_t z;	// r5
	int32_t b;	// r9
	int32_t rb; // r4

	posX = this->posX;
	v4 = (int32_t)posX;
	v5 = posX < (float)(int32_t)posX;
	minY = this->boundingBox.minY;
	v7 = (int32_t)minY;
	if(v5) {
		--v4;
	}
	v8 = minY < (float)(int32_t)minY;
	posZ = this->posZ;
	z = (int32_t)posZ;
	if(v8) {
		--v7;
	}
	if(posZ < (float)(int32_t)posZ) {
		--z;
	}
	b = this->level->getBrightness(LightLayer::Sky, v4, v7, z);
	if(b > (int32_t)(this->random.genrand_int32() & 0x1F)) {
		return 0;
	}
	rb = this->level->getRawBrightness(v4, v7, z);
	return rb <= (int32_t)(this->random.genrand_int32() & 7);
}

Monster::~Monster() {
}
void Monster::tick() {
	Mob::tick();
	if(!this->level->isClientMaybe && !this->level->difficulty) {
		this->remove();
	}
}
bool_t Monster::hurt(Entity* a2, int32_t a3) {
	int32_t r; // r0

	r = Mob::hurt(a2, a3);
	if(r) {
		if(this->rider != a2 && this->ridingAt != a2 && a2 != this) {
			this->attackTarget = 0;
			if(a2) {
				this->attackTarget = a2->entityId;
				if(a2->isMob()) {
					this->lastHurtByMaybe = a2->entityId;
				}
			}
		}
		return 1;
	}
	return 0;
}

int32_t Monster::getCreatureBaseType() {
	return 1;
}
void Monster::aiStep() {
	this->updateAttackAnim();
	if(this->getBrightness(1) > 0.5) {
		this->noActionTime += 2;
	}
	Mob::aiStep();
}
bool_t Monster::canSpawn() {
	if(this->isDarkEnoughToSpawn()) {
		return PathfinderMob::canSpawn();
	}
	return 0;
}
bool_t Monster::doHurtTarget(Entity* a2) {
	this->swing();
	return a2->hurt(this, this->attackDamage);
}
float Monster::getWalkTargetValue(int32_t x, int32_t y, int32_t z) {
	return 0.5 - this->level->getBrightness(x, y, z);
}
Entity* Monster::findAttackTarget() {
	Entity* np; // r5

	np = (Entity*)this->level->getNearestPlayer(this, 16.0);
	if(!np || !this->canSee(np)) {
		return 0;
	}
	return np;
}
void Monster::checkHurtTarget(Entity* a2, float a3) {
	int32_t v5; // r0

	if(this->attackTime <= 0 && a3 < 2.0 && a2->boundingBox.maxY > this->boundingBox.minY && a2->boundingBox.minY < this->boundingBox.maxY) {
		v5 = this->getAttackTime();
		this->attackTime = v5;
		this->doHurtTarget(a2);
	}
}
int32_t Monster::getAttackDamage(Entity*) {
	return this->attackDamage;
}
int32_t Monster::getAttackTime() {
	return 20;
}
