#pragma once
#include <entity/ai/Goal.hpp>
#include <math/Vec3.hpp>

struct PathfinderMob;
struct PanicGoal: Goal
{
	PathfinderMob* holder;
	float speedMultiplier;
	Vec3 target;

	PanicGoal(PathfinderMob*, float);

	virtual ~PanicGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
};
