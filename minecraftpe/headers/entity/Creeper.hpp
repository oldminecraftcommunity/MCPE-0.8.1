#pragma once
#include <entity/Monster.hpp>

struct Creeper: Monster
{
	int32_t swellTime, prevSwellTime;
	int32_t field_C8C;

	Creeper(Level*);
	int32_t getSwellDir();
	float getSwelling(float);
	void setSwellDir(int32_t);

	virtual ~Creeper();
	virtual void tick();
	virtual bool_t interactWithPlayer(Player*);
	virtual int32_t getEntityTypeId() const;
	virtual float getBaseSpeed();
	virtual int32_t getMaxHealth();
	virtual int32_t getDeathLoot();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual bool_t useNewAi();
	virtual void checkHurtTarget(Entity*, float);
	virtual void checkCantSeeTarget(Entity*, float);

};
