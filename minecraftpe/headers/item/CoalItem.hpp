#pragma once
#include <item/Item.hpp>

struct CoalItem: Item
{
	TextureUVCoordinateSet field_48;

	CoalItem(int32_t);
	virtual ~CoalItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual std::string getDescriptionId(const ItemInstance*);
};
