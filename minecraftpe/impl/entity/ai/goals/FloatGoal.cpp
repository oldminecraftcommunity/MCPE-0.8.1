#include <entity/ai/goals/FloatGoal.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <entity/ai/JumpControl.hpp>
#include <entity/path/PathNavigation.hpp>

FloatGoal::FloatGoal(Mob* a2)
	: Goal() {
	this->holder = a2;
	this->setRequiredControlFlags(4);
	a2->getNavigation()->setCanFloat(1);
}

FloatGoal::~FloatGoal() {
}
bool_t FloatGoal::canUse() {
	if(this->holder->isInWater()) return 1;
	return this->holder->isInLava();
}
void FloatGoal::tick() {
	float v2 = this->holder->level->random.nextFloat();
	if(v2 < 0.8) {
		this->holder->getJumpControl()->jump();
	}
}
