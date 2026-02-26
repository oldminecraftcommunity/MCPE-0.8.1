#pragma once
#include <item/TileItem.hpp>

struct LeafTileItem: TileItem
{
	LeafTileItem(int32_t);

	virtual ~LeafTileItem();
	virtual TextureUVCoordinateSet* getIcon(int32_t, int32_t, bool_t);
	virtual int32_t getLevelDataForAuxValue(int32_t);

};
