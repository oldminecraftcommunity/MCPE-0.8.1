#include <util/_ChunkSorter.hpp>

bool_t _ChunkSorter::operator()(const IntPair& a2, const IntPair& a3) const {
	int32_t x; // r3
	int32_t y; // r0

	x = this->pair.x;
	y = this->pair.y;
	return (a2.y - y) * (a2.y - y) + (a2.x - x) * (a2.x - x) < (a3.y - y) * (a3.y - y) + (a3.x - x) * (a3.x - x);
}
