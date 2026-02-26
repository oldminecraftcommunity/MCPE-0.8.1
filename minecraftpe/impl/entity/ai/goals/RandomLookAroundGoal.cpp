#include <entity/ai/goals/RandomLookAroundGoal.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <entity/ai/LookControl.hpp>
#include <math.h>

RandomLookAroundGoal::RandomLookAroundGoal(Mob* a2) {
	this->holder = a2;
	this->zOff = 0;
	this->xOff = 0;
	this->ticksLeft = 0;
	this->setRequiredControlFlags(3);
}

RandomLookAroundGoal::~RandomLookAroundGoal() {
}
bool_t RandomLookAroundGoal::canUse() {
	return this->holder->level->random.nextFloat() < 0.02;
}
bool_t RandomLookAroundGoal::canContinueToUse() {
	return this->ticksLeft >= 0;
}
void RandomLookAroundGoal::start() {
	float v2;	 // s14
	float v3;	 // s15
	Mob* holder; // r3
	float v6;	 // s15

	v2 = this->holder->level->random.nextFloat();
	v3 = cos((float)((float)(3.1416 + 3.1416) * v2));
	this->xOff = v3;
	v6 = sin((float)((float)(3.1416 + 3.1416) * v2));
	holder = this->holder;
	this->zOff = v6;
	this->ticksLeft = holder->level->random.genrand_int32() % 20 + 20;
}
void RandomLookAroundGoal::tick() {
	--this->ticksLeft;
	this->holder->getLookControl()->setLookAt(holder->posX + this->xOff, holder->posY + holder->getHeadHeight(), this->holder->posZ + this->zOff, 10, this->holder->getMaxHeadXRot());
}
