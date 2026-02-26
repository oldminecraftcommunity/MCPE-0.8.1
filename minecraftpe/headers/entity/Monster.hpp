#pragma once
#include <entity/PathfinderMob.hpp>

struct Monster: PathfinderMob
{
	int32_t attackDamage, lastHurtByMaybe;

	Monster(Level*);
	bool_t isDarkEnoughToSpawn();

	virtual ~Monster();
	virtual void tick();
	virtual bool_t hurt(Entity*, int32_t);

	virtual int32_t getCreatureBaseType();
	virtual float getBaseSpeed() = 0;
	virtual void aiStep();
	virtual bool_t canSpawn();
	virtual bool_t doHurtTarget(Entity*);
	virtual float getWalkTargetValue(int32_t, int32_t, int32_t);
	virtual Entity* findAttackTarget();
	virtual void checkHurtTarget(Entity*, float);
	virtual int32_t getAttackDamage(Entity*);
	virtual int32_t getAttackTime();
};
