#pragma once
#include <tile/Tile.hpp>

struct IceTile : Tile{
	IceTile(int32_t, const std::string&, Material*);

	virtual ~IceTile();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual void playerDestroy(Level*, Player*, int32_t, int32_t, int32_t, int32_t);
};
