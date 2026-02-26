#pragma once
#include <tile/Tile.hpp>

struct EntityTile : Tile{

	EntityTile(int32_t, const struct Material*);
	EntityTile(int32_t, const std::string&, const struct Material*);


	virtual ~EntityTile();
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);
	virtual void onRemove(Level*, int32_t, int32_t, int32_t);
	virtual void triggerEvent(Level*, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual struct TileEntity* newTileEntity();
};
