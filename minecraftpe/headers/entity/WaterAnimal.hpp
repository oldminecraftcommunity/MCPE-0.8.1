#pragma once
#include <entity/PathfinderMob.hpp>

struct WaterAnimal: PathfinderMob
{
	WaterAnimal(Level*);
	int32_t getExperienceReward(Player*); //release feature leaks :scream:
	/*funny considering the code is based on pre beta 1.8 prob*/

	virtual ~WaterAnimal();
	virtual int32_t getCreatureBaseType();
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual bool_t isWaterMob();
	virtual int32_t getAmbientSoundInterval();
	virtual float getBaseSpeed();
	virtual bool_t canSpawn();
	virtual bool_t removeWhenFarAway();
};
