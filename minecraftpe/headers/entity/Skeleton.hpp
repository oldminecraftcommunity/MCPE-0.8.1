#pragma once
#include <entity/Monster.hpp>

struct Skeleton: Monster
{
	ItemInstance heldItem;
	int32_t field_C9C;

	Skeleton(Level*);

	virtual ~Skeleton();
	virtual int32_t getEntityTypeId() const;
	virtual float getBaseSpeed();
	virtual int32_t getMaxHealth();
	virtual void aiStep();
	virtual ItemInstance* getCarriedItem();
	virtual int32_t getDeathLoot();
	virtual void dropDeathLoot();
	virtual const char_t* getAmbientSound();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual bool_t useNewAi();
	virtual void checkHurtTarget(Entity*, float);
	virtual int32_t getUseDuration();
};
