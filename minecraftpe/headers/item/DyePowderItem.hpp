#pragma once
#include <item/Item.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

struct DyePowderItem: Item
{
	static std::string COLOR_DESCS[];
	TextureAtlasTextureItem field_48;

	DyePowderItem(int32_t);

	virtual ~DyePowderItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	virtual void interactEnemy(ItemInstance*, Mob*, Player*);
	virtual std::string getName(const ItemInstance*);
	virtual std::string getDescriptionId(const ItemInstance*);

};
