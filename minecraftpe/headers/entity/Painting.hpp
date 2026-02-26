#pragma once
#include <entity/HangingEntity.hpp>

struct Motive;
struct Painting: HangingEntity
{
	const Motive* motive;

	Painting(Level*);
	Painting(Level*, int32_t, int32_t, int32_t, int32_t);
	Painting(Level*, int32_t, int32_t, int32_t, int32_t, const std::string&);
	void setRandomMotive(int32_t);

	virtual ~Painting();
	virtual float getShadowRadius();
	virtual bool_t isPickable();
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual int32_t getWidth();
	virtual int32_t getHeight();
	virtual void dropItem();

};
