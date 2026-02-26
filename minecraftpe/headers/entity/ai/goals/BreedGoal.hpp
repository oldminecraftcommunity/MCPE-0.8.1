#pragma once
#include <entity/ai/Goal.hpp>
#include <util/TempEPtr.hpp>

struct Animal;
struct Level;
struct BreedGoal: Goal
{
	Animal* animal;
	Level* level;
	TempEPtr<Animal> target;
	int32_t inUseTicks;
	float speedMultiplier;

	BreedGoal(Animal*, float);
	void breed();
	Animal* getFreePartner();

	virtual ~BreedGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void stop();
	virtual void tick();
	virtual void setLevel(Level*);
};
