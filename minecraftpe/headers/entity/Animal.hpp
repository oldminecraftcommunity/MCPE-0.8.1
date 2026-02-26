#pragma once
#include <entity/AgableMob.hpp>

struct Animal: AgableMob
{
	int32_t inLove;

	Animal(Level*);
	bool_t canMate(const Animal*);
	bool_t isInLove() const;
	void resetLove();

	virtual ~Animal();
	virtual bool_t interactWithPlayer(Player*);
	virtual bool_t hurt(Entity*, int32_t);
	virtual int32_t getCreatureBaseType();
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual int32_t getAmbientSoundInterval();
	virtual void aiStep();
	virtual bool_t canSpawn();
	virtual bool_t removeWhenFarAway();
	virtual float getWalkTargetValue(int32_t, int32_t, int32_t);
	virtual Entity* findAttackTarget();
	virtual bool_t isFood(const ItemInstance*);
	virtual Mob* getBreedOffspring(Animal*) = 0;
};
