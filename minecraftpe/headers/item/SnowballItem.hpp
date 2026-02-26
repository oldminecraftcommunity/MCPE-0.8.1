#pragma once
#include <item/Item.hpp>

struct SnowballItem: Item
{
	SnowballItem(int id);
	virtual ~SnowballItem();
	virtual ItemInstance* use(ItemInstance*, Level*, Player*);
};
