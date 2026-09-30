#pragma once
#include <util/IntPair.hpp>

struct _ChunkSorter
{
	IntPair pair;

	bool_t operator()(const IntPair& a2, const IntPair& a3) {
		int x = this->pair.x;
		int y = this->pair.y;
		return (a2.y - y) * (a2.y - y) + (a2.x - x) * (a2.x - x) < (a3.y - y) * (a3.y - y) + (a3.x - x) * (a3.x - x);
	}
};
