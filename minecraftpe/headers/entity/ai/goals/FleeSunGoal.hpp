#pragma once
#include <entity/ai/Goal.hpp>
#include <math/Vec3.hpp>

struct PathfinderMob;
struct Level;

struct FleeSunGoal: Goal
{
	PathfinderMob* holder;
	Vec3 target;
	float speedMultiplier;
	Level* level;

	FleeSunGoal(PathfinderMob*, float);
	bool_t getHidePos(Vec3*);

	virtual ~FleeSunGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void setLevel(Level*);
};
