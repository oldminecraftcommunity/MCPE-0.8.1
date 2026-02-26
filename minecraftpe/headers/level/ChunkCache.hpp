#pragma once
#include <_types.h>
#include <level/gen/ChunkSource.hpp>
struct ChunkStorage;
struct LevelChunk;
struct Level;
struct ChunkCache: ChunkSource
{
	int8_t field_4, field_5, field_6, field_7;
	int32_t lastChunkX, lastChunkZ;
	LevelChunk* emptyChunk;
	ChunkSource* generatorSource;
	ChunkStorage* chunkStorage;
	LevelChunk* chunks[256];
	Level* level;
	LevelChunk* lastChunk;

	virtual ~ChunkCache();
	virtual bool_t hasChunk(int32_t, int32_t);
	virtual LevelChunk* getChunk(int32_t, int32_t);
	virtual LevelChunk* create(int32_t, int32_t);
	virtual void postProcess(ChunkSource*, int32_t, int32_t);
	virtual bool_t tick();
	virtual bool_t shouldSave();
	virtual void saveAll(bool_t);
	virtual std::vector<Biome::MobSpawnerData> getMobsAt(const MobCategory&, int32_t, int32_t, int32_t);
	virtual std::string gatherStats();
};
