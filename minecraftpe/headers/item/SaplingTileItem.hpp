#pragma once
#include <item/TileItem.hpp>

struct SaplingTileItem: TileItem
{
	SaplingTileItem(int32_t);
	virtual ~SaplingTileItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual int32_t getLevelDataForAuxValue(int32_t);
};
