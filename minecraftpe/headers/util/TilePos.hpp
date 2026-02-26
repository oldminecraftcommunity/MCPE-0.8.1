#pragma once
#include <_types.h>
#include <stdlib.h>
#include <bitset>
struct TilePos{
	int32_t x, y, z;

	bool_t operator<(const TilePos&);
	bool_t operator==(const TilePos&) const; //TODO this thing seems to be not in the game
};

template<>
struct std::hash<TilePos>
{
	//i hate c++ so much
	size_t operator()(const TilePos& a2) const noexcept {
		return 0xEF88B * a2.y + 0x88F9FA * a2.x + a2.z;
	}
};
