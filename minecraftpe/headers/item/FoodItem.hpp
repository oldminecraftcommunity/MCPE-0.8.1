#pragma once
#include <item/Item.hpp>

struct FoodItem: Item
{
	int32_t healAmount;
	float field_48;
	int8_t field_4C, field_4D, field_4E, field_4F;

	FoodItem(int32_t id, int32_t healAmount, float f48, int8_t f4C);
	virtual ~FoodItem();
	virtual ItemInstance* use(ItemInstance*, struct Level*, Player*);
	virtual int32_t getMaxUseDuration();
	virtual ItemInstance useTimeDepleted(ItemInstance*, Level*, Player*);
	virtual int32_t getUseAnimation();
	virtual bool_t isFood();
};
