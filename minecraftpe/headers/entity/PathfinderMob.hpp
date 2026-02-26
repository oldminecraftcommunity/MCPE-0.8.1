#pragma once
#include <entity/Mob.hpp>

struct Path;
struct PathfinderMob: Mob
{
	int32_t attackTarget;
	bool_t _shouldHoldGround;
	int8_t field_C71, field_C72, field_C73;
	int32_t inPanicTicksMaybe;
	Path* path;

	PathfinderMob(Level*);
	int32_t getNoActionTime();
	bool_t isPathFinding();
	void setPath(Path*);

	virtual ~PathfinderMob();
	virtual bool_t canSpawn();
	virtual void updateAi();
	virtual float getWalkingSpeedModifier();
	virtual Entity* getAttackTarget();
	virtual void setAttackTarget(Entity*);
	virtual float getWalkTargetValue(int32_t, int32_t, int32_t);
	virtual Entity* findAttackTarget();
	virtual void checkHurtTarget(Entity*, float);
	virtual void checkCantSeeTarget(Entity*, float);
	virtual bool_t shouldHoldGround();
	virtual void findRandomStrollLocation();
};
