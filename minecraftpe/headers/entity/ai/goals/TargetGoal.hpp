#pragma once
#include <entity/ai/Goal.hpp>
#include <entity/Player.hpp>
#include <entity/ai/Sensing.hpp>
struct Mob;
struct TargetGoal: Goal
{
	Mob* mob;
	float radius;
	bool field_C, field_D;

	TargetGoal(Mob* mob, float rad, int8_t c) {
		this->radius = rad;
		this->mob = mob;
		this->field_C = c;
	}
	bool_t canAttack(Mob* a2, bool_t a3) {
		if (a2) {
			if (a2 != this->mob && a2->isAlive()) {
				if (a2->boundingBox.maxY > this->mob->boundingBox.minY && a2->boundingBox.minY < this->mob->boundingBox.maxY && (!a2->isPlayer() || a3 || !((Player*) (a2))->abilities.invulnerable)) {
					if(!this->field_C) return 1;
					if(this->mob->getSensing()->canSee(a2)) return 1;
				}
			}
		}
		return 0;
	}

	virtual ~TargetGoal(){}
	virtual bool_t canContinueToUse() {
		Entity* v2 = this->mob->getTarget();
		if(!v2) return 0;
		if(!v2->isAlive()) return 0;
		if(this->mob->distanceToSqr(v2) > (this->radius * this->radius)) return 0;
		if (!this->field_C || this->mob->getSensing()->canSee(v2)) return 1;
		return 0;
	}
	virtual void stop() {
		this->mob->setTarget(0);
	}
};
