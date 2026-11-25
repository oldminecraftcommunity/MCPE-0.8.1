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

bool_t RandomStrollGoal::canUse() {
	if(this->holder->getNoActionTime() > 99) return 0;
	if(this->holder->level->random.nextInt(120)) return 0;

	Vec3 v3(0, 0, 0);
	if(RandomPos::generateRandomPos(v3, this->holder, 10, 7, 0)) {
		this->targetX = v3.x;
		this->targetY = v3.y;
		this->targetZ = v3.z;
		return 1;
	}
	return 0;
}
bool_t RandomStrollGoal::canContinueToUse() {
	return !this->holder->getNavigation()->isDone();
}
void RandomStrollGoal::start() {
	this->holder->getNavigation()->moveTo(this->targetX, this->targetY, this->targetZ, this->speedMultiplier);
}
