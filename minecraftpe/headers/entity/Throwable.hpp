#pragma once
#include <entity/Entity.hpp>

struct Throwable: Entity
{
	int32_t shake;
	bool_t inGround;
	byte field_11D, field_11E, field_11F;
	int32_t auxData;
	int32_t ticksInGround, ticksInAir;
	int32_t xTile, yTile, zTile;
	int32_t inTile;

	Throwable(Level*);
	Throwable(Level*, Mob*);
	Throwable(Level*, float, float, float);

	void _init();
	void shoot(const Vec3&, float, float);
	void shoot(float, float, float, float, float);

	virtual ~Throwable();
	virtual void lerpMotion(float, float, float);
	virtual void tick();
	virtual float getShadowHeightOffs();
	virtual bool_t shouldRenderAtSqrDistance(float);
	virtual int32_t getAuxData();
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual float getThrowPower();
	virtual float getThrowUpAngleOffset();
	virtual float getGravity();
	virtual void onHit(const HitResult&) = 0;
};
