#include <entity/ai/goals/LookAtPlayerGoal.hpp>
#include <entity/ai/LookControl.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>

LookAtPlayerGoal::LookAtPlayerGoal(Mob* a2, float a3)
	: Goal() {
	this->mob = a2;
	this->maxDistance = a3;
	this->startChance = 0.02;
	this->setRequiredControlFlags(2);
	this->ticksLeft = 0;
}
LookAtPlayerGoal::LookAtPlayerGoal(Mob* a2, float a3, float a4){
	this->mob = a2;
	this->maxDistance = a3;
	this->startChance = a4;
	this->setRequiredControlFlags(2);
	this->ticksLeft = 0;
}

LookAtPlayerGoal::~LookAtPlayerGoal() {
}
bool_t LookAtPlayerGoal::canUse() {
	float v2;		 // s14
	Player* nearest; // r0
	Level* level;	 // r0

	v2 = this->mob->level->random.nextFloat();
	if(v2 >= this->startChance) {
		return 0;
	}
	nearest = this->mob->level->getNearestPlayer(this->mob, this->maxDistance);
	if(nearest != this->target.entity) {
		if(nearest) {
			this->target.entityId = nearest->entityId;
			level = nearest->level;
			this->target.level = level;
			level->registerTemporaryPointer(&this->target);
			this->target.locked = 0;
		} else {
			this->target.unset();
		}
	}
	return this->target.lock() != 0;
}
bool_t LookAtPlayerGoal::canContinueToUse() {
	Entity* v3;	 // r0
	Entity* mob; // r6
	Entity* v6;	 // r0

	if(this->target.lock() && (v3 = this->target.lock(), v3->isAlive()) && (mob = (Entity*)this->mob, v6 = this->target.lock(), mob->distanceToSqr(v6) <= (float)(this->maxDistance * this->maxDistance))) {
		return this->ticksLeft > 0;
	} else {
		return 0;
	}
}
void LookAtPlayerGoal::start() {
	this->ticksLeft = this->mob->level->random.genrand_int32() % 40 + 40;
}
void LookAtPlayerGoal::stop() {
	if(this->target.entity) {
		this->target.unset();
	}
}
void LookAtPlayerGoal::tick() {
	LookControl* look; // r8
	float posX;		   // r7
	float posY;		   // s16
	float v6;		   // s16
	float posZ;		   // r6
	float a6;		   // r0

	look = this->mob->getLookControl();
	posX = this->target.lock()->posX;
	posY = this->target.lock()->posY;
	v6 = posY + this->target.lock()->getHeadHeight();
	posZ = this->target.lock()->posZ;
	a6 = this->mob->getMaxHeadXRot();
	look->setLookAt(posX, v6, posZ, 10.0, a6);
	--this->ticksLeft;
}
