#include <entity/ai/goals/HurtByTargetGoal.hpp>
#include <entity/Mob.hpp>
HurtByTargetGoal::HurtByTargetGoal(Mob* mob, float radius)
	: TargetGoal(mob, radius, 0) {
	this->field_D = 0;
	this->setRequiredControlFlags(1);
}
HurtByTargetGoal::~HurtByTargetGoal() {
}
bool_t HurtByTargetGoal::canUse() {
	return this->canAttack(this->mob->getLastHurtByMob(), 1);
}
void HurtByTargetGoal::start() {
	mob->setTarget(mob->getLastHurtByMob());
}
