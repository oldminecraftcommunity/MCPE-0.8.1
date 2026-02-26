#pragma once
#include <item/Item.hpp>

struct SeedItem: Item
{
	int32_t plantId, placeId;
	SeedItem(int32_t id, int32_t plantId, int32_t placeId);

	virtual ~SeedItem();
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	virtual bool_t isSeed();
};
