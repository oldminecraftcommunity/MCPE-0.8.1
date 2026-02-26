#pragma once
#include <item/Item.hpp>

struct MinecartItem: Item
{
	int32_t type;

	MinecartItem(int32_t, int32_t);

	virtual ~MinecartItem();
	virtual bool_t useOn(ItemInstance*, Player*, struct Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
};
