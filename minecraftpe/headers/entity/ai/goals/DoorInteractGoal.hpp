#pragma once
#include <entity/ai/Goal.hpp>

struct Mob;
struct Tile;

struct DoorInteractGoal: Goal
{
	Mob* holder;
	int32_t doorX, doorY, doorZ;
	Tile* doorTile;
	bool_t closeToTarget;
	byte align[3];
	float targetX, targetZ;

	DoorInteractGoal(Mob*);

	Tile* getDoorTile(int32_t, int32_t, int32_t);

	virtual ~DoorInteractGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void tick();
};
