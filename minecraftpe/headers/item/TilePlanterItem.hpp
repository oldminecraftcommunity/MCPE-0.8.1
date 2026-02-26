#pragma once
#include <item/Item.hpp>

struct TilePlanterItem: Item
{
	int32_t blockID;
	TilePlanterItem(int32_t id, Tile* tile);

	virtual ~TilePlanterItem();
	virtual bool_t useOn(ItemInstance*, Player*, struct Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	virtual bool_t isEmissive(int32_t);
};
