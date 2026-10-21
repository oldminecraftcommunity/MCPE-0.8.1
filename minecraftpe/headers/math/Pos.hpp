#pragma once
#include <_types.h>

struct Pos
{
	int32_t x, y, z;
	Pos(int x, int y, int z)
		: x(x)
		, y(y)
		, z(z) {
	}
	Pos(const Pos&) = default;
	Pos() {
	}
	bool_t operator==(const Pos& a2) {
		return this->x == a2.x && this->y == a2.y && this->z == a2.z;
	}
};
