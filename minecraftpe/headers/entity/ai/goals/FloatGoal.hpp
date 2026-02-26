#pragma once
#include <entity/ai/Goal.hpp>

struct Mob;

struct FloatGoal: Goal
{
	Mob* holder;

	FloatGoal(Mob*);

	virtual ~FloatGoal();
	virtual bool_t canUse();
	virtual void tick();
};
