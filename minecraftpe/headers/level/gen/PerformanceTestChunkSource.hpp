#pragma once
#include <level/gen/ChunkSource.hpp>

struct Level;
struct PerformanceTestChunkSource: ChunkSource
{
	int32_t field_4;
	Level* level;

	~PerformanceTestChunkSource();
	virtual bool_t hasChunk(int32_t, int32_t);
	virtual LevelChunk* getChunk(int32_t, int32_t);
	virtual LevelChunk* create(int32_t, int32_t);
	virtual void postProcess(ChunkSource*, int32_t, int32_t);
	virtual bool_t tick();
	virtual bool_t shouldSave();
	virtual std::string gatherStats();

};
