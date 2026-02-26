#include <entity/ai/goals/ArrowAttackGoal.hpp>
#include <entity/Arrow.hpp>
#include <entity/Mob.hpp>
#include <entity/Snowball.hpp>
#include <entity/ai/LookControl.hpp>
#include <entity/ai/Sensing.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>
#include <math.h>

ArrowAttackGoal::ArrowAttackGoal(Mob* a2, float a3, int32_t a4, int32_t a5)
	: Goal() {
	this->seenTicks = 0;
	this->holder = a2;
	this->speedMultiplier = a3;
	this->attackType = a4;
	this->level = a2->level;
	this->delayBetweenAttack = a5;
	this->setRequiredControlFlags(3);
}
void ArrowAttackGoal::fireAtTarget() {
	Mob* v2;			// r0
	int32_t attackType; // r3
	Mob* v4;			// r5
	Entity* v5;			// r6
	Level* level;		// r7
	float posY;			// s18
	float v8;			// s17
	float v9;			// s18
	float v10;			// s16
	float v11;			// s14
	Entity* holder;		// r5

	v2 = this->target.lock();
	attackType = this->attackType;
	v4 = v2;
	if(attackType == 1) {
		v5 = new Arrow(this->level, this->holder, v4, 1.6, 12.0);
		level = this->level;
	} else {
		if(attackType != 2) {
			return;
		}
		v5 = new Snowball(this->level, this->holder);
		posY = v4->posY;
		v8 = v4->posX - this->holder->posX;
		v9 = (float)((float)(posY + v4->getHeadHeight()) - 1.1) - v5->posY;
		v10 = v4->posZ - this->holder->posZ;
		v11 = sqrt((float)((float)(v10 * v10) + (float)(v8 * v8))) * 0.200000003;
		((Throwable*)v5)->shoot(v8, v9 + v11, v10, 1.6, 12.0);
		level = this->level;
	}

	level->playSound(this->holder, "random.bow", 1.0, 1.0 / (float)((float)(this->holder->level->random.nextFloat() * 0.4) + 0.8));
	this->level->addEntity(v5);
}

ArrowAttackGoal::~ArrowAttackGoal() {
}
bool_t ArrowAttackGoal::canUse() {
	Level* level; // r0

	Entity* result = this->holder->getTarget();
	if(result) {
		if(result != this->target.entity) {
			this->target.entityId = result->entityId;
			level = result->level;
			this->target.level = level;
			level->registerTemporaryPointer(&this->target);
			this->target.locked = 0;
		}
		return 1;
	}
	return 0;
}
bool_t ArrowAttackGoal::canContinueToUse() {
	if(this->target.lock()) {
		if(this->canUse()) {
			return 1;
		} else {
			return !this->holder->getNavigation()->isDone();
		}
	}
	return 0;
}
void ArrowAttackGoal::stop() {
	if(this->target.entity) this->target.unset();
}
void ArrowAttackGoal::tick() {
	Mob* v2;			  // r5
	float v3;			  // s16
	Sensing* sensing;	  // r0
	bool_t canSee;		  // r6
	PathNavigation* nav2; // r0
	PathNavigation* nav;  // r0
	LookControl* look;	  // r0
	int32_t v9;			  // r3

	v2 = this->target.lock();
	v3 = this->holder->distanceToSqr(v2->posX, v2->boundingBox.minY, v2->posZ);
	sensing = this->holder->getSensing();
	canSee = sensing->canSee(v2);
	if(canSee) {
		++this->seenTicks;
	} else {
		this->seenTicks = 0;
	}
	if(v3 <= 100.0 && this->seenTicks > 19) {
		nav = this->holder->getNavigation();
		nav->stop();
	} else {
		nav2 = this->holder->getNavigation();
		nav2->moveTo(v2, this->speedMultiplier);
	}
	look = this->holder->getLookControl();
	look->setLookAt(v2, 30.0, 30.0);
	v9 = (this->attackTimeout - 1) & ~((this->attackTimeout - 1) >> 31);
	this->attackTimeout = v9;
	if(!v9 && v3 <= 100.0 && canSee) {
		this->fireAtTarget();
		this->attackTimeout = this->delayBetweenAttack;
	}
}
void ArrowAttackGoal::setLevel(Level* l) {
	this->level = l;
}
