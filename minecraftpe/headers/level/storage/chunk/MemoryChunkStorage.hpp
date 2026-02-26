#pragma once
#include <level/storage/chunk/ChunkStorage.hpp>

struct MemoryChunkStorage : ChunkStorage
{
	virtual ~MemoryChunkStorage();
};
