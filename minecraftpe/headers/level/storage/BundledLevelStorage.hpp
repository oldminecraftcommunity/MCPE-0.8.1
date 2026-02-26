#pragma once
#include <level/storage/MemoryLevelStorage.hpp>
#include <level/storage/chunk/ChunkStorage.hpp>

#include <string>

struct BinaryBlob;
struct RandomLevelSource;
struct BundledLevelStorage: MemoryLevelStorage, ChunkStorage
{
	std::string levelNameMaybe;
	struct LevelData* levelData;
	Level* field_14;
	int32_t field_18;
	RandomLevelSource* field_1C;
	struct Minecraft* minecraft;

	BundledLevelStorage(struct Minecraft*, const std::string&);

	virtual ~BundledLevelStorage();
	virtual LevelData* prepareLevel(Level*);
	virtual ChunkStorage* createChunkStorage(Dimension*);
	virtual bool_t load(Player*);
	virtual struct LevelChunk* load(Level*, int32_t, int32_t);
	virtual void save2(Level*, LevelChunk*);
	virtual void getChunkData(int32_t, int32_t);
	virtual void freeChunkData(int32_t, int32_t, BinaryBlob*);
};
