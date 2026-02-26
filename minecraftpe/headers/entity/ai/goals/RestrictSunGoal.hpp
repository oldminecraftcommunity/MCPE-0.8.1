#pragma once
#include <entity/ai/Goal.hpp>

struct PathfinderMob;
struct RestrictSunGoal: Goal
{
	PathfinderMob* holder;

	RestrictSunGoal(PathfinderMob*);

	virtual ~RestrictSunGoal();
	virtual bool_t canUse();
	virtual void start();
	virtual void stop();
};
