#pragma once
#include <item/DiggerItem.hpp>

struct PickaxeItem: DiggerItem
{
	PickaxeItem(int32_t, const Item::Tier&);

	virtual ~PickaxeItem();
	virtual float getDestroySpeed(ItemInstance*, Tile*);
	virtual bool_t canDestroySpecial(const Tile*);

};
