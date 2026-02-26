#pragma once
#include <_types.h>
#include <vector>
struct Level;
struct LevelChunk;

struct ChunkStorage{
	virtual ~ChunkStorage();
	virtual struct LevelChunk* load(Level*, int32_t, int32_t);
	virtual void save(Level*, LevelChunk*);
	virtual void saveEntities(Level*, LevelChunk*);
	virtual void saveAll(Level*, std::vector<LevelChunk*>&);
	virtual void tick();
	virtual void flush();
};
