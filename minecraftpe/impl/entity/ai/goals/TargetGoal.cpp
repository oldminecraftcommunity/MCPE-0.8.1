#include <entity/ai/goals/TargetGoal.hpp>
#include <entity/Player.hpp>
#include <entity/ai/Sensing.hpp>

TargetGoal::TargetGoal(Mob* mob, float rad, int8_t c) {
	this->radius = rad;
	this->mob = mob;
	this->field_C = c;
}
bool_t TargetGoal::canAttack(Mob* a2, bool_t a3) {
	Mob* mob;		  // r3
	Sensing* sensing; // r0

	if(a2) {
		if(a2 != this->mob && a2->isAlive()) {
			mob = this->mob;
			if(a2->boundingBox.maxY > mob->boundingBox.minY && a2->boundingBox.minY < mob->boundingBox.maxY && (!a2->isPlayer() || a3 || !((Player*)a2)->abilities.invulnerable)) {
				if(!this->field_C) {
					return 1;
				}
				sensing = this->mob->getSensing();
				if(sensing->canSee(a2)) {
					return 1;
				}
			}
		}
	}
	return 0;
}

TargetGoal::~TargetGoal() {
}
bool_t TargetGoal::canContinueToUse() {
	Entity* v2;		  // r0
	Entity* v3;		  // r5
	Sensing* sensing; // r0

	v2 = this->mob->getTarget();
	v3 = v2;
	if(v2) {
		if(v2->isAlive() && this->mob->distanceToSqr(v3) <= (float)(this->radius * this->radius)) {
			if(!this->field_C) {
				return 1;
			}
			sensing = this->mob->getSensing();
			if(sensing->canSee(v3)) {
				return 1;
			}
		}
	}
	return 0;
}
void TargetGoal::stop() {
	this->mob->setTarget(0);
}
