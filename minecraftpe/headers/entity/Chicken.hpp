#pragma once
#include <entity/Animal.hpp>

struct Chicken: Animal
{
	int8_t field_C88;
	float field_C8C, field_C90, field_C94, field_C98, field_C9C;
	int32_t nextEggCounter;

	Chicken(Level*);

	virtual ~Chicken(){}
	virtual int32_t getEntityTypeId() const;
	virtual void causeFallDamage(float);
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual float getBaseSpeed() {
		return 0.25;
	}
	virtual int32_t getMaxHealth();
	virtual void aiStep();
	virtual void dropDeathLoot();
	virtual const char_t* getAmbientSound();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual bool_t useNewAi();
	virtual bool_t isFood(const ItemInstance*) const;
	virtual Mob* getBreedOffspring(Animal*);
};
