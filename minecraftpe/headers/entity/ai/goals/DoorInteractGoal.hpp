#pragma once
#include <entity/ai/Goal.hpp>

struct Mob;
struct DoorTile;

struct DoorInteractGoal: Goal
{
	Mob* holder;
	int32_t doorX, doorY, doorZ;
	DoorTile* doorTile;
	bool_t closeToTarget;
	char align[3];
	float targetX, targetZ;

	DoorInteractGoal(Mob*);

	DoorTile* getDoorTile(int32_t, int32_t, int32_t);

	virtual ~DoorInteractGoal() {
	}
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void tick();
};
