#pragma once
#include <item/Item.hpp>
#include <tile/Tile.hpp>

struct WeaponItem: Item
{
	Item::Tier tier;
	int32_t damage;

	WeaponItem(int32_t a2, const Item::Tier& a3) :
		Item(a2), tier(a3) {
		this->maxStackSize = 1;
		this->setMaxDamage(a3.durability);
		this->damage = a3.damageAgainstEntity + 4;
	}

	virtual ~WeaponItem() {
	}
	virtual ItemInstance* use(ItemInstance* a2, Level*, Player*) {
		return a2;
	}
	virtual int32_t getMaxUseDuration() const {
		return 72000;
	}
	virtual float getDestroySpeed(ItemInstance* a2, Tile* a3) {
		if (a3->blockID == Tile::web->blockID) return 15.0;

		return 1.5f;
	}
	virtual bool_t canDestroySpecial(const Tile* a2) const {
		return a2->blockID == Tile::web->blockID;
	}
	virtual int32_t getAttackDamage(Entity*) {
		return this->damage;
	}
	virtual void hurtEnemy(ItemInstance* a2, Mob* a3, Mob* a4) {
		a2->hurtAndBreak(1, a4);
	}
	virtual bool_t mineBlock(ItemInstance* a2, int32_t, int32_t, int32_t, int32_t, Mob* a7) {
		a2->hurtAndBreak(2, a7);
		return 1;
	}
	virtual bool_t isHandEquipped() const {
		return 1;
	}
};
