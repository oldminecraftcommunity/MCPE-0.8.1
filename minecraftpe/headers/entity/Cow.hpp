#pragma once
#include <entity/Animal.hpp>

struct Cow: Animal
{
	int32_t milkedTicks;

	Cow(Level*);

	virtual ~Cow();
	virtual void tick();
	virtual bool_t interactWithPlayer(Player*);
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual float getBaseSpeed();
	virtual int32_t getMaxHealth();
	virtual int32_t getDeathLoot();
	virtual void dropDeathLoot();
	virtual float getSoundVolume();
	virtual const char_t* getAmbientSound();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual bool_t useNewAi();
	virtual Mob* getBreedOffspring(Animal*);
};
