#pragma once
#include <level/gen/ChunkSource.hpp>

struct Level;
struct PerformanceTestChunkSource: ChunkSource
{
	int32_t field_4;
	Level* level;

	~PerformanceTestChunkSource() {
	}
	virtual bool_t hasChunk(int32_t, int32_t) {
		return 1;
	}
	virtual LevelChunk* getChunk(int32_t x, int32_t z) {
		return this->create(x, z);
	}
	virtual LevelChunk* create(int32_t, int32_t);
	virtual void postProcess(ChunkSource*, int32_t, int32_t) {
	}
	virtual bool_t tick() {
		return 0;
	}
	virtual bool_t shouldSave() {
		return 0;
	}
	virtual std::string gatherStats() {
		return "PerformanceTestChunkSource";
	}
};
