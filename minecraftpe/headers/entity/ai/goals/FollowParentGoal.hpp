#pragma once
#include <entity/ai/Goal.hpp>
#include <util/TempEPtr.hpp>

struct Animal;

struct FollowParentGoal: Goal
{
	Animal* holder;
	TempEPtr<Animal> parent;
	float speedMultiplier;
	int32_t ticksFollowing;

	FollowParentGoal(Animal*, float);

	virtual ~FollowParentGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void stop();
	virtual void tick();
};
