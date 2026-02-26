#pragma once
#include <item/TileItem.hpp>

struct StoneSlabTileItem: TileItem
{
	StoneSlabTileItem(int32_t);
	virtual ~StoneSlabTileItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	virtual int32_t getLevelDataForAuxValue(int32_t);
	virtual std::string getName(const ItemInstance*);
	virtual std::string getDescriptionId(const ItemInstance*);
};
