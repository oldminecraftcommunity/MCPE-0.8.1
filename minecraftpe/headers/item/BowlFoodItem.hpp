#pragma once
#include <item/FoodItem.hpp>

struct BowlFoodItem: FoodItem
{
	BowlFoodItem(int32_t, int32_t);
	virtual ~BowlFoodItem();
	virtual ItemInstance useTimeDepleted(ItemInstance*, Level*, Player*);
};
