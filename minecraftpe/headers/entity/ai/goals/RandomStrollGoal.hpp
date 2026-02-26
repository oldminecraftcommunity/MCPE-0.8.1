#pragma once
#include <entity/ai/Goal.hpp>
#include <math/Vec3.hpp>

struct PathfinderMob;
struct RandomStrollGoal: Goal
{
	PathfinderMob* holder;
	Vec3 target;
	float speedMultiplier;

	RandomStrollGoal(PathfinderMob*, float);

	virtual ~RandomStrollGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
};
