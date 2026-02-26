#pragma once
#include <item/Item.hpp>

struct Level;
struct HangingEntityItem: Item
{
	int32_t entityId;
	HangingEntityItem(int32_t, int32_t);
	struct HangingEntity* createEntity(Level*, int32_t, int32_t, int32_t, int32_t);


	virtual ~HangingEntityItem();
	virtual bool_t useOn(ItemInstance *, Player *, Level *, int32_t, int32_t, int32_t, int32_t, float, float, float);
};
