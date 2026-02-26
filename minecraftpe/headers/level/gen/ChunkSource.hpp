#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <level/biome/Biome.hpp>

struct LevelChunk;
struct ChunkSource{
	virtual ~ChunkSource();
	virtual bool_t hasChunk(int32_t, int32_t) = 0;
	virtual LevelChunk* getChunk(int32_t, int32_t) = 0;
	virtual LevelChunk* create(int32_t, int32_t) = 0;
	virtual void postProcess(ChunkSource*, int32_t, int32_t) = 0;
	virtual bool_t tick() = 0;
	virtual bool_t shouldSave() = 0;
	virtual void saveAll(bool_t);
	virtual std::vector<Biome::MobSpawnerData> getMobsAt(const MobCategory&, int32_t, int32_t, int32_t) = 0;
	virtual std::string gatherStats() = 0;
};
