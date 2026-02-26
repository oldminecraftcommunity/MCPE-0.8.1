#pragma once
#include <item/Item.hpp>

struct HoeItem: Item
{
	Item::Tier tier;

	HoeItem(int32_t, Item::Tier);

	virtual ~HoeItem();
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	virtual bool_t isHandEquipped();
};
