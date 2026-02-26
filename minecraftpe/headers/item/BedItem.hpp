#pragma once
#include <item/Item.hpp>

struct BedItem: Item
{
	BedItem(int32_t id);
	virtual ~BedItem();
	virtual bool_t useOn(ItemInstance *, Player *, Level *, int32_t, int32_t, int32_t, int32_t, float, float, float);
};
