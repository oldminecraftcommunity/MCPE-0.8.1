#pragma once
#include <entity/Mob.hpp>

struct FlyingMob: Mob
{
	FlyingMob(Level*);

	virtual ~FlyingMob();
	virtual void causeFallDamage(float);
	virtual bool_t onLadder();
	virtual void travel(float, float);
};
