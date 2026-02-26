#pragma once
#include <item/Item.hpp>

struct Tile;
struct ShearsItem: Item
{
	ShearsItem(int32_t id);
	virtual ~ShearsItem();
	virtual float getDestroySpeed(ItemInstance*, Tile*);
	virtual bool_t canDestroySpecial(const Tile*);
	virtual bool_t mineBlock(ItemInstance*, int32_t, int32_t, int32_t, int32_t, Mob*);
};
