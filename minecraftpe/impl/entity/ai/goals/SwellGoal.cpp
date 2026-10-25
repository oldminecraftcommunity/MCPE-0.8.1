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
			this->target.level->registerTemporaryPointer(&this->target);
			this->target.locked = 0;
		} else {
			this->target.unset();
		}
	}
}
void SwellGoal::stop() {
	TempEPtr<Mob>* ptr = &this->target;
	if(ptr->entity) {
		ptr->unset();
	}
}
void SwellGoal::tick() {
	this->target.lock();

	Mob* v5 = this->target.entity;
	int sd = -1;
	if(v5) {
		if(this->holder->distanceToSqr(this->target.entity) > 49 || !this->holder->getSensing()->canSee(v5)) {
			sd = 1;
		}
	}
	this->holder->setSwellDir(sd);
}
