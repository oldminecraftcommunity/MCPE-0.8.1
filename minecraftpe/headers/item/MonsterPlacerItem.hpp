#pragma once
#include <item/Item.hpp>

struct MonsterPlacerItem: Item
{
	TextureUVCoordinateSet field_48, field_60, field_78, field_90;

	MonsterPlacerItem(int32_t);
	static Mob* spawnMobAt(struct Level*, int32_t, float, float, float);

	virtual ~MonsterPlacerItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	virtual std::string getName(const ItemInstance*);

};
