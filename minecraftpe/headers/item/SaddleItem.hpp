#pragma once
#include <item/Item.hpp>

struct SaddleItem: Item
{
	SaddleItem(int32_t);
	virtual ~SaddleItem();
	virtual void hurtEnemy(ItemInstance*, Mob*, Mob*);
	virtual void interactEnemy(ItemInstance*, Mob*, Player*);
};
