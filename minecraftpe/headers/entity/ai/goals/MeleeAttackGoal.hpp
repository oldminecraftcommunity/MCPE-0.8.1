#pragma once
#include <entity/ai/Goal.hpp>
#include <util/TempEPtr.hpp>

struct Mob;
struct Path;

struct MeleeAttackGoal: Goal
{
	Level* level;
	Mob* attacker;
	TempEPtr<Mob> target;
	int32_t field_24;
	float speedMultiplier;
	bool_t field_2C;
	int8_t field_2D, field_2E, field_2F;
	Path* path;
	int32_t field_34;

	MeleeAttackGoal(Mob*, float, bool_t);
	void _init(Mob*, float, bool_t);

	virtual ~MeleeAttackGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void stop();
	virtual void tick();
	virtual void setLevel(Level*);
};
