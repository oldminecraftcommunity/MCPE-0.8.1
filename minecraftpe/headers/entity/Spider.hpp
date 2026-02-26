#pragma once
#include <entity/Monster.hpp>

struct Spider: Monster
{
	int32_t field_C88;

	Spider(Level*);
	float getModelScale();
	bool_t isClimbing();
	int32_t makeStepSound();
	void setClimbing(bool_t);

	virtual ~Spider();
	virtual void tick();
	virtual float getShadowRadius();
	virtual void makeStuckInWeb();
	virtual int32_t getEntityTypeId() const;
	virtual bool_t onLadder();
	virtual float getBaseSpeed();
	virtual int32_t getMaxHealth();
	virtual void aiStep();
	virtual int32_t getDeathLoot();
	virtual const char_t* getAmbientSound();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual Entity* findAttackTarget();
	virtual void checkHurtTarget(Entity*, float);
};
