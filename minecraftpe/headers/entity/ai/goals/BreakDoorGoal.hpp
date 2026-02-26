#pragma once
#include <entity/ai/goals/DoorInteractGoal.hpp>

struct BreakDoorGoal: DoorInteractGoal
{
	int32_t ticksLeft;

	BreakDoorGoal(Mob*);

	virtual ~BreakDoorGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void tick();
};
