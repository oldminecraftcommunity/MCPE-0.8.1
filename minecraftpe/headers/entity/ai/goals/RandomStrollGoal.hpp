#pragma once
#include <entity/ai/Goal.hpp>

struct PathfinderMob;
struct RandomStrollGoal: Goal
{
	PathfinderMob* holder;
	float targetX, targetY, targetZ;
	float speedMultiplier;

	RandomStrollGoal(PathfinderMob*, float);

	virtual ~RandomStrollGoal(){}
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
};
