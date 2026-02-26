#pragma once
#include <item/Item.hpp>

struct Level;
struct SignItem: Item
{
	SignItem(int32_t id);

	virtual ~SignItem();
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
};
