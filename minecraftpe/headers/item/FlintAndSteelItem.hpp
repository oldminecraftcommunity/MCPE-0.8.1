#pragma once
#include <item/Item.hpp>

struct FlintAndSteelItem: Item
{
	FlintAndSteelItem(int32_t);

	virtual ~FlintAndSteelItem();
	virtual bool_t useOn(ItemInstance*, Player*, struct Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
};
