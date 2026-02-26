#pragma once
#include <item/Item.hpp>

struct TileItem: Item
{
	int32_t blockID;

	TileItem(int32_t);

	virtual ~TileItem();
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	virtual std::string getDescriptionId();
	virtual std::string getDescriptionId(const ItemInstance*);
	virtual bool_t isEmissive(int32_t);

};
