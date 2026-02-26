#pragma once
#include <entity/ai/Goal.hpp>

struct Mob;

struct RandomLookAroundGoal: Goal
{
	Mob* holder;
	float xOff, zOff;
	int32_t ticksLeft;

	RandomLookAroundGoal(Mob*);

	virtual ~RandomLookAroundGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void tick();
};
