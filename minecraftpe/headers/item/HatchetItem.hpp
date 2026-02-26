#pragma once
#include <item/DiggerItem.hpp>

struct HatchetItem: DiggerItem
{
	HatchetItem(int32_t, const Item::Tier&);

	virtual ~HatchetItem();
	virtual float getDestroySpeed(ItemInstance*, Tile*);
};
