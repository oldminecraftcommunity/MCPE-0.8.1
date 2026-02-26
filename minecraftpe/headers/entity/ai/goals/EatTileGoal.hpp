#pragma once
#include <entity/ai/Goal.hpp>

struct Mob;
struct Level;

struct EatTileGoal: Goal
{
	Mob* holder;
	Level* level;
	int32_t ticksLeft;

	EatTileGoal(Mob*);

	virtual ~EatTileGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void stop();
	virtual void tick();
	virtual int32_t getEatAnimationTick();
	virtual void setLevel(Level*);
};
