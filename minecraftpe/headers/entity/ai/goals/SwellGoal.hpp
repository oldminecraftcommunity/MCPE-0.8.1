#pragma once
#include <entity/ai/Goal.hpp>
#include <util/TempEPtr.hpp>

struct Creeper;
struct Mob;
struct SwellGoal: Goal
{
	Creeper* holder;
	TempEPtr<Mob> target;

	SwellGoal(Creeper*);

	virtual ~SwellGoal();
	virtual bool_t canUse();
	virtual void start();
	virtual void stop();
	virtual void tick();
};
