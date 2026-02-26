#pragma once
#include <tile/Tile.hpp>

struct DirectionalTile : Tile{
	DirectionalTile(int32_t, const Material*);
	virtual ~DirectionalTile();
};
