#pragma once
#include <tile/Tile.hpp>

struct OreTile : Tile{
	OreTile(int32_t, const std::string&);

	virtual ~OreTile();
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
