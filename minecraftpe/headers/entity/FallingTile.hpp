#pragma once
#include <entity/Entity.hpp>

struct FallingTile: Entity
{
	int32_t blockID;
	int32_t blockMetaMaybe;
	int32_t fallTime;

	FallingTile(Level*);
	FallingTile(Level*, float, float, float, int32_t, int32_t);
	Level* getLevel();
	void init();

	virtual ~FallingTile();
	virtual void tick();
	virtual float getShadowRadius();
	virtual float getShadowHeightOffs();
	virtual bool_t isPickable();
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
};
