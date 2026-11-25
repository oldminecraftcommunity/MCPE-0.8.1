#pragma once
#include <entity/ai/Goal.hpp>

struct PathfinderMob;
struct PanicGoal: Goal
{
	PathfinderMob* holder;
	float speedMultiplier;
	float targetX, targetY, targetZ;

	PanicGoal(PathfinderMob*, float);

	virtual ~PanicGoal(){}
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
};
