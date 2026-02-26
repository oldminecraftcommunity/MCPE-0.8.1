#pragma once
#include <_types.h>

struct Pos
{
	int32_t x, y, z;

	bool_t operator==(const Pos&);
};
