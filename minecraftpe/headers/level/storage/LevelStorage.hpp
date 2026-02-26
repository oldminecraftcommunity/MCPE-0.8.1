#pragma once
#include <_types.h>
#include <vector>
#include <level/storage/LevelData.hpp>
struct Player;
struct LevelData;
struct Level;
struct Dimension;
struct LevelChunk;
struct ChunkStorage;
struct LevelStorage{

	virtual ~LevelStorage();
	virtual LevelData* prepareLevel(Level*) = 0;
	virtual ChunkStorage* createChunkStorage(Dimension*) = 0;
	virtual void saveLevelData(LevelData&, std::vector<Player*>*) = 0;
	virtual void saveLevelData(LevelData&);
	virtual bool_t load(Player*);
	virtual bool_t save(Player*);
	virtual void closeAll() = 0;
	virtual void saveGame(Level*);
	virtual void loadEntities(Level*, LevelChunk*);

};
