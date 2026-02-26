#pragma once
#include <entity/PathfinderMob.hpp>

struct AgableMob: PathfinderMob
{
	int32_t age;

	AgableMob(Level*);

	int32_t getAge();
	void setAge(int32_t);

	virtual ~AgableMob();
	virtual float getShadowRadius();
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual void aiStep();
	virtual bool_t isBaby();
};
