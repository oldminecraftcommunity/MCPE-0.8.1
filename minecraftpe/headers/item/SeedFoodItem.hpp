#pragma once
#include <item/FoodItem.hpp>

struct SeedFoodItem: FoodItem
{
	int32_t plantId, placeId;
	SeedFoodItem(int32_t id, int32_t healAmount, float f48, int8_t f4C, int32_t plantID, int32_t placeID);
	virtual ~SeedFoodItem();
	virtual bool_t useOn(ItemInstance*, Player*, struct Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
};
