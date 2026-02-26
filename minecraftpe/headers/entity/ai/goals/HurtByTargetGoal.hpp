#pragma once
#include <entity/ai/goals/TargetGoal.hpp>

struct HurtByTargetGoal: TargetGoal
{
	HurtByTargetGoal(Mob*, float radius);

	virtual ~HurtByTargetGoal();
	virtual bool_t canUse();
	virtual void start();
};
