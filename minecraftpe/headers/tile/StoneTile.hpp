#pragma once
#include <tile/Tile.hpp>

struct StoneTile : Tile{
	StoneTile(int32_t, const std::string&);

	virtual ~StoneTile();
	virtual int32_t getResource(int32_t, struct Random*);

};
