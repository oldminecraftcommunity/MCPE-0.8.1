#pragma once
#include <entity/ai/Goal.hpp>
#include <util/TempEPtr.hpp>

struct Level;
struct Mob;

struct ArrowAttackGoal: Goal
{
	Level* level;
	Mob* holder;
	TempEPtr<Mob> target;
	int32_t attackTimeout;
	float speedMultiplier;
	int32_t seenTicks, attackType, delayBetweenAttack;

	ArrowAttackGoal(Mob*, float, int32_t, int32_t);
	void fireAtTarget();

	virtual ~ArrowAttackGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void stop();
	virtual void tick();
	virtual void setLevel(Level*);
};
