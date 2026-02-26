#pragma once
#include <entity/Entity.hpp>

struct ItemEntity: Entity
{
	ItemInstance itemInstance;
	int32_t field_130;
	int32_t delayBeforePickup;
	float hoverStart;
	int32_t age, health, lifeTime;

	ItemEntity(Level*);
	ItemEntity(Level*, float, float, float, const ItemInstance&);
	bool_t checkInTile(float, float, float);
	int32_t getLifeTime();

	virtual ~ItemEntity();
	virtual void tick();
	virtual bool_t isInWater();
	virtual void playerTouch(Player*);
	virtual bool_t hurt(Entity*, int32_t);
	virtual int32_t getEntityTypeId() const;
	virtual bool_t isItemEntity();
	virtual void burn(int32_t);
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
};
