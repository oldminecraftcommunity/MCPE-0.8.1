#include <entity/ai/goals/PanicGoal.hpp>
#include <entity/PathfinderMob.hpp>
#include <entity/path/PathNavigation.hpp>
#include <util/RandomPos.hpp>

PanicGoal::PanicGoal(PathfinderMob* a2, float a3) {
	this->holder = a2;
	this->speedMultiplier = a3;
	this->setRequiredControlFlags(1);
}

PanicGoal::~PanicGoal() {
}
bool_t PanicGoal::canUse() {
	if(!this->holder->getLastHurtByMob()) {
		return 0;
	}
	Vec3 v3(0, 0, 0);
	if(!RandomPos::generateRandomPos(v3, this->holder, 5, 4, 0)) {
		return 0;
	}
	this->target = v3;
	return 1;
}
bool_t PanicGoal::canContinueToUse() {
	return !this->holder->getNavigation()->isDone();
}
void PanicGoal::start() {
	this->holder->getNavigation()->moveTo(this->target.x, this->target.y, this->target.z, this->speedMultiplier);
}
