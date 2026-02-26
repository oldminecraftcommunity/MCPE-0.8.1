#pragma once
#include <entity/ai/goals/DoorInteractGoal.hpp>

struct OpenDoorGoal: DoorInteractGoal
{
	bool_t field_28;
	int8_t field_29, field_2A, field_2B;
	int32_t ticksLeft;

	OpenDoorGoal(Mob*, bool_t);

	virtual ~OpenDoorGoal();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void stop();
	virtual void tick();
};
