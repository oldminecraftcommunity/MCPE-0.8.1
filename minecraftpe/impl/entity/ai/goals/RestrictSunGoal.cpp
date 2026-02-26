#include <entity/ai/goals/RestrictSunGoal.hpp>
#include <entity/PathfinderMob.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>

RestrictSunGoal::RestrictSunGoal(PathfinderMob* a2) : Goal() {
	this->holder = a2;
}

RestrictSunGoal::~RestrictSunGoal() {
}
bool_t RestrictSunGoal::canUse() {
	return this->holder->level->isDay();
}
void RestrictSunGoal::start(){
	return this->holder->getNavigation()->setAvoidSun(1);
}
void RestrictSunGoal::stop() {
	return this->holder->getNavigation()->setAvoidSun(0);
}
