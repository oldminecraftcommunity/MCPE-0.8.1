#include <entity/ai/goals/SwellGoal.hpp>
#include <entity/Creeper.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>
#include <entity/ai/Sensing.hpp>

SwellGoal::SwellGoal(Creeper* a2)
	: Goal() {
	this->holder = a2;
	this->setRequiredControlFlags(1);
}

SwellGoal::~SwellGoal() {
}
bool_t SwellGoal::canUse() {
	if(this->holder->getSwellDir() > 0) return 1;
	Entity* res = this->holder->getTarget();
	if(res) {
		return this->holder->distanceToSqr(res) < 9;
	}
	return 0;
}
void SwellGoal::start() {
	PathNavigation* nav = this->holder->getNavigation();
	nav->stop();
	Entity* v3 = this->holder->getTarget();
	if(v3 != this->target.entity) {
		if(v3) {
			this->target.entityId = v3->entityId;
			this->target.level = v3->level;
			v3->level->registerTemporaryPointer(&this->target);
			this->target.locked = 0;
		} else {
			this->target.unset();
		}
	}
}
void SwellGoal::stop() {
	if(this->target.entity) {
		this->target.unset();
	}
}
void SwellGoal::tick() {
	Level* level;	  // r0
	int32_t entityId; // r1
	Entity* e;		  // r0
	Mob* v5;		  // r5
	Creeper* holder;  // r0
	float v7;		  // s14
	Sensing* sensing; // r0
	int32_t v9;		  // r1

	this->target.lock();

	v5 = this->target.entity;
	holder = this->holder;
	if(v5) {
		v7 = holder->distanceToSqr(this->target.entity);
		holder = this->holder;
		if(v7 <= 49.0) {
			sensing = holder->getSensing();
			if(sensing->canSee(v5)) {
				holder = this->holder;
				v9 = 1;
				goto LABEL_13;
			}
			holder = this->holder;
		}
	}
	v9 = -1;
LABEL_13:
	holder->setSwellDir(v9);
}
