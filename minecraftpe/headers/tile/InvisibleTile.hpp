#pragma once
#include <tile/Tile.hpp>

struct InvisibleTile : Tile{

	InvisibleTile(int32_t, const std::string&, Material*);

	virtual ~InvisibleTile();
	virtual int32_t getRenderShape();
};
