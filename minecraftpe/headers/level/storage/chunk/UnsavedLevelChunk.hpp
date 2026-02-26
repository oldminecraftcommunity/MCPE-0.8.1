#pragma once
#include <_types.h>
struct LevelChunk;
struct UnsavedLevelChunk
{
	int32_t index;
	int32_t timeMs;
	LevelChunk* chunk;
};
