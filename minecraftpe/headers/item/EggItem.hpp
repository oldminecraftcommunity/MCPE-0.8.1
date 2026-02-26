#pragma once
#include <item/Item.hpp>
struct EggItem: Item
{
	EggItem(int32_t);
	virtual ~EggItem();
	virtual ItemInstance* use(ItemInstance*, Level*, Player*);
};
