#include <entity/ai/goals/MeleeAttackGoal.hpp>
#include <entity/path/Path.hpp>
#include <entity/Mob.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>
#include <entity/ai/LookControl.hpp>
#include <entity/ai/Sensing.hpp>

MeleeAttackGoal::MeleeAttackGoal(Mob* a2, float a3, bool_t a4) : Goal(){
	this->_init(a2, a3, a4);
}
void MeleeAttackGoal::_init(Mob* a2, float a3, bool_t a4) {
	this->attacker = a2;
	this->field_2C = a4;
	this->level = a2->level;
	this->speedMultiplier = a3;
	this->setRequiredControlFlags(3);
	this->field_24 = 0;
	this->path = 0;
	this->field_34 = 0;
}

MeleeAttackGoal::~MeleeAttackGoal() {
	if(this->path) {
		delete this->path;
	}
}
bool_t MeleeAttackGoal::canUse() {
	Entity* result; // r0
	Level* v3; // r0
	Path* path; // r5

	result = this->attacker->getTarget();
	if(result) {
		if(result != this->target.entity) {
			this->target.entityId = result->entityId;
			v3 = result->level;
			this->target.level = v3;
			v3->registerTemporaryPointer(&this->target);
			this->target.locked = 0;
		}
		path = this->path;
		if(path) {
			delete path;
		}
		this->path = this->attacker->getNavigation()->createPath(this->target.lock());
		return this->path != 0;
	}
	return 0;
}
bool_t MeleeAttackGoal::canContinueToUse() {
	Mob* v3; // r0

	if(this->attacker->getTarget()) {
		if(this->target.lock() && (v3 = this->target.lock(), v3->isAlive())) {
			if(this->field_2C) {
				return 1;
			} else {
				return !this->attacker->getNavigation()->isDone();
			}
		} else {
			return 0;
		}
	}
	return 0;
}
void MeleeAttackGoal::start() {
	this->attacker->getNavigation()->moveTo(this->path, this->speedMultiplier);
	this->path = 0;
	this->field_34 = 0;
}
void MeleeAttackGoal::stop() {
	if(this->target.entity) {
		this->target.unset();
	}
	this->attacker->getNavigation()->stop();
}
void MeleeAttackGoal::tick() {
	uint32_t v7;   // r1
	Mob* attacker; // r0
	Entity* v11;   // r6
	float v12;	   // s15
	float posX;	   // r8
	float minY;	   // r7
	Mob* v16;	   // r4
	int32_t v19;   // r3

	this->attacker->getLookControl()->setLookAt(this->target.lock(), 30.0, 30.0);
	if(this->field_2C || this->attacker->getSensing()->canSee(this->target.lock())) {
		v19 = this->field_34 - 1;
		this->field_34 = v19;
		if(v19 <= 0) {
			v7 = this->attacker->level->random.genrand_int32() % 7;
			attacker = this->attacker;
			this->field_34 = v7 + 4;
			attacker->getNavigation()->moveTo(this->target.lock(), this->speedMultiplier);
		}
	}
	v11 = (Entity*)this->attacker;
	this->field_24 = (this->field_24 - 1) & ~((this->field_24 - 1) >> 31);
	v12 = v11->entityWidth + v11->entityWidth;
	posX = this->target.lock()->posX;
	minY = this->target.lock()->boundingBox.minY;
	if(v11->distanceToSqr(posX, minY, this->target.lock()->posZ) <= (float)(v12 * v12) && this->field_24 <= 0) {
		this->field_24 = 20;
		v16 = this->attacker;
		v16->doHurtTarget(this->target.lock());
	}
}
void MeleeAttackGoal::setLevel(Level* l  ) {
	this->level = l;
}
