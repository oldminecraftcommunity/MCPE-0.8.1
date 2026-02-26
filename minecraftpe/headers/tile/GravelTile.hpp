#pragma once
#include <tile/HeavyTile.hpp>

struct GravelTile : HeavyTile{
	GravelTile(int32_t, const std::string&);
	virtual ~GravelTile();
	virtual int getResource(int32_t, Random*);
};
