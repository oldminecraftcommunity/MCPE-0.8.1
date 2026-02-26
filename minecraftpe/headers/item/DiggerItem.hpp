#pragma once
#include <item/Item.hpp>
#include <vector>

struct Tile;
struct DiggerItem: Item
{
	float efficiencyMultiplier;
	const Item::Tier* tier;
	int32_t damageAgainstEntity;
	std::vector<Tile*> field_50;
	bool_t field_5C[256];

	void setTiles(const std::vector<Tile*>&);

	DiggerItem(int32_t, const Item::Tier&);
	virtual ~DiggerItem();
	virtual float getDestroySpeed(ItemInstance*, Tile*);
	virtual int32_t getAttackDamage(Entity*);
	virtual void hurtEnemy(ItemInstance*, Mob*, Mob*);
	virtual bool_t mineBlock(ItemInstance*, int32_t, int32_t, int32_t, int32_t, Mob*);
	virtual bool_t isHandEquipped();

};
