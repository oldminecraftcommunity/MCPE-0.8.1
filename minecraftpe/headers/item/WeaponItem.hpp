#pragma once
#include <item/Item.hpp>

struct WeaponItem: Item
{
	Item::Tier tier;
	int32_t damage;

	WeaponItem(int32_t, const Item::Tier&);

	virtual ~WeaponItem();
	virtual ItemInstance* use(ItemInstance*, Level*, Player*);
	virtual int32_t getMaxUseDuration();
	virtual float getDestroySpeed(ItemInstance*, Tile*);
	virtual bool_t canDestroySpecial(const Tile*);
	virtual int32_t getAttackDamage(Entity*);
	virtual void hurtEnemy(ItemInstance*, Mob*, Mob*);
	virtual bool_t mineBlock(ItemInstance*, int32_t, int32_t, int32_t, int32_t, Mob*);
	virtual bool_t isHandEquipped();
};
