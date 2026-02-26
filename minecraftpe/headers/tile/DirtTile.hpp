#pragma once
#include <tile/Tile.hpp>

struct DirtTile : Tile{
	DirtTile(int32_t, std::string, Material*);
	virtual ~DirtTile();
};
