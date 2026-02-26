#pragma once
#include <tile/Tile.hpp>

struct SnowTile : Tile{
	SnowTile(int32_t, const std::string&, Material*);

	virtual ~SnowTile();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
};
