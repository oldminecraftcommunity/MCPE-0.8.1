#pragma once
#include <tile/Bush.hpp>

struct FlowerTile : Bush{
	bool_t _randomWalk(struct Level*, int32_t&, int32_t&, int32_t&, int32_t);
	FlowerTile(int32_t id, const std::string& name);

	virtual ~FlowerTile();
	virtual bool_t onFertilized(Level*, int32_t, int32_t, int32_t);
};
