#pragma once
#include <tile/Tile.hpp>

struct LightGemTile : Tile{
	LightGemTile(int32_t, const std::string&, const struct Material*);

	virtual ~LightGemTile();
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
};
