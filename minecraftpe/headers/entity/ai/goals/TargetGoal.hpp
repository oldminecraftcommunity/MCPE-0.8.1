#pragma once
#include <entity/ai/Goal.hpp>
struct Mob;
struct TargetGoal: Goal
{
	Mob* mob;
	float radius;
	int8_t field_C, field_D, field_E, field_F;

	TargetGoal(Mob*, float rad, int8_t c);
	bool_t canAttack(Mob*, bool_t);

	virtual ~TargetGoal();
	virtual bool_t canContinueToUse();
	virtual void stop();
};
