#include <entity/ai/goals/FleeSunGoal.hpp>
#include <entity/PathfinderMob.hpp>
#include <entity/path/PathNavigation.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>

FleeSunGoal::FleeSunGoal(PathfinderMob* a2, float a3) {
	this->holder = a2;
	this->speedMultiplier = a3;
	this->level = a2->level;
	this->setRequiredControlFlags(1);
}
bool_t FleeSunGoal::getHidePos(Vec3* a2) {
	int32_t v4;		  // r5
	Random* p_random; // r6
	float posX;		  // s18
	int32_t v7;		  // r1
	int32_t v8;		  // r0
	float minY;		  // s18
	int32_t v10;	  // r10
	int32_t v11;	  // r1
	int32_t v12;	  // r0
	float posZ;		  // s18
	int32_t v14;	  // r9
	int32_t v15;	  // r1
	int32_t v16;	  // r8

	v4 = 10;
	p_random = &this->holder->level->random;
	do {
		posX = this->holder->posX;
		v7 = p_random->genrand_int32() % 0x14;
		v8 = Mth::floor((float)(posX + (float)v7) - 10.0);
		minY = this->holder->boundingBox.minY;
		v10 = v8;
		v11 = p_random->genrand_int32() % 6;
		v12 = Mth::floor((float)(minY + (float)v11) - 3.0);
		posZ = this->holder->posZ;
		v14 = v12;
		v15 = p_random->genrand_int32() % 0x14;
		v16 = Mth::floor((float)(posZ + (float)v15) - 10.0);
		if(!this->level->canSeeSky(v10, v14, v16) && this->holder->getWalkTargetValue(v10, v14, v16) < 0.0) {
			a2->x = (float)v10;
			a2->y = (float)v14;
			a2->z = (float)v16;
			return 1;
		}
		--v4;
	} while(v4);
	return 0;
}

FleeSunGoal::~FleeSunGoal() {
}
bool_t FleeSunGoal::canUse() {
	PathfinderMob* holder; // r5
	int32_t v3;			   // r6
	int32_t v4;			   // r0

	if(!this->level->isDay()) {
		return 0;
	}
	if(!this->holder->isOnFire()) {
		return 0;
	}
	holder = this->holder;
	v3 = Mth::floor(holder->posX);
	v4 = Mth::floor(holder->posZ);
	if(!this->level->canSeeSky(v3, (int32_t)holder->boundingBox.minY, v4)) {
		return 0;
	}
	Vec3 v6(0, 0, 0);
	if(!this->getHidePos(&v6)) {
		return 0;
	}
	this->target = v6;
	return 1;
}
bool_t FleeSunGoal::canContinueToUse() {
	return this->holder->getNavigation()->isDone();
}
void FleeSunGoal::start() {
	this->holder->getNavigation()->moveTo(this->target.x, this->target.y, this->target.z, this->speedMultiplier);
}
void FleeSunGoal::setLevel(Level* a2) {
	this->level = a2;
}
