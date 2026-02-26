#include <entity/ai/goals/RandomStrollGoal.hpp>
#include <entity/PathfinderMob.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>
#include <util/RandomPos.hpp>

RandomStrollGoal::RandomStrollGoal(PathfinderMob* ent, float speed)
	: Goal() {
	this->holder = ent;
	this->speedMultiplier = speed;
	this->setRequiredControlFlags(3);
}

RandomStrollGoal::~RandomStrollGoal() {
}
bool_t RandomStrollGoal::canUse() {
	if(this->holder->getNoActionTime() > 99 || this->holder->level->random.genrand_int32() % 120) {
		return 0;
	}
	Vec3 v3(0, 0, 0);
	if(RandomPos::generateRandomPos(v3, this->holder, 10, 7, 0)) {
		this->target = v3;
		return 1;
	}
	return 0;
}
bool_t RandomStrollGoal::canContinueToUse() {
	return !this->holder->getNavigation()->isDone();
}
void RandomStrollGoal::start() {
	this->holder->getNavigation()->moveTo(this->target.x, this->target.y, this->target.z, this->speedMultiplier);
}
