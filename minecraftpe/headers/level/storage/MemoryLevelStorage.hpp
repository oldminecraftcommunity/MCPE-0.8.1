#pragma once
#include <level/storage/LevelStorage.hpp>


struct MemoryLevelStorage: LevelStorage
{
	ChunkStorage* chunkStorage;


	MemoryLevelStorage(ChunkStorage*); //inlined in mcpe?
	virtual ~MemoryLevelStorage();
	virtual LevelData* prepareLevel(Level*);
	virtual ChunkStorage* createChunkStorage(Dimension*);
	virtual void saveLevelData(LevelData&, std::vector<Player*>*);
	virtual void closeAll();

};
