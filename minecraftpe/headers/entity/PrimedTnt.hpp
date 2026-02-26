#pragma once
#include <entity/Entity.hpp>

struct PrimedTnt: Entity
{
	int32_t ticksUntilExplode;

	PrimedTnt(Level*);
	PrimedTnt(Level*, float, float, float);
	void explode();

	virtual ~PrimedTnt();
	virtual void tick();
	virtual float getShadowRadius();
	virtual float getShadowHeightOffs();
	virtual bool_t isPickable();
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
};
