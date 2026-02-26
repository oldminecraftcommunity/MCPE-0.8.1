#pragma once
#include <item/DiggerItem.hpp>

struct ShovelItem: DiggerItem
{
	ShovelItem(int32_t, const Item::Tier&);

	virtual ~ShovelItem();
	bool_t canDestroySpecial(const Tile*);
};
