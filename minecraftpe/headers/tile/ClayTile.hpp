#pragma once
#include <tile/Tile.hpp>

struct ClayTile : Tile{
	ClayTile(int32_t, std::string, Material*);

	virtual ~ClayTile();
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
};
