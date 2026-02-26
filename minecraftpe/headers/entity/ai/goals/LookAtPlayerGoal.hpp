#pragma once
#include <entity/ai/Goal.hpp>
#include <util/TempEPtr.hpp>

struct Entity;
struct Mob;

struct LookAtPlayerGoal: Goal
{
	Mob* mob;
	TempEPtr<Entity> target;
	float maxDistance;
	int32_t ticksLeft;
	float startChance;

	LookAtPlayerGoal(Mob*, float);
	LookAtPlayerGoal(Mob*, float, float);

	virtual ~LookAtPlayerGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void stop();
	virtual void tick();
};
