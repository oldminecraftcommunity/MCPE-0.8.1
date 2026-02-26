#pragma once
#include <_types.h>

struct ChunkPos
{
	int32_t x, z;

	bool_t operator<(const ChunkPos&) const;
};
