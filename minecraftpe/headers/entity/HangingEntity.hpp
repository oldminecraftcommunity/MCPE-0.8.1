#pragma once
#include <entity/Entity.hpp>

struct HangingEntity: Entity
{
	int32_t direction, tileX, tileY, tileZ;
	int32_t surviveTicker;

	HangingEntity(Level*);
	HangingEntity(Level*, int32_t, int32_t, int32_t, int32_t);
	void init();
	float offs(int32_t);
	void setDir(int32_t);
	void setPosition(int32_t, int32_t, int32_t);

	virtual ~HangingEntity();
	virtual void move(float, float, float);
	virtual void tick();
	float getBrightness(float);
	virtual bool_t interactWithPlayer(Player*);
	virtual void push(float, float, float);
	virtual bool_t isPickable();
	virtual bool_t hurt(Entity*, int32_t);
	virtual bool_t isHangingEntity();
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual bool_t survives();
	virtual int32_t getWidth() = 0;
	virtual int32_t getHeight() = 0;
	virtual void dropItem() = 0;
};
