#pragma once
#include <level/storage/LevelStorage.hpp>
#include <level/storage/chunk/ChunkStorage.hpp>
#include <list>
struct UnsavedLevelChunk;
struct RegionFile;
struct ExternalFileLevelStorage: LevelStorage, ChunkStorage
{
	std::string field_8;
	std::string anotherDataFolder, dataFolder;
	LevelData* levelData;
	RegionFile* regionFile;
	int32_t field_1C;
	Level* level;
	int32_t field_24, field_28;
	std::list<UnsavedLevelChunk> field_2C; //linked list in stlport
	//TODO field_30 seems to be related to field_2C
	int32_t field_34;

	ExternalFileLevelStorage(const std::string&, const std::string&);
	static bool_t readLevelData(const std::string&, LevelData&);
	static void readPlayerData(const std::string&, LevelData&);
	static void saveLevelData(const std::string&, LevelData&, std::vector<Player*>*);
	void savePendingUnsavedChunks(int32_t);
	static bool_t writeLevelData(const std::string&, LevelData&, const std::vector<Player*>*);

	virtual ~ExternalFileLevelStorage();
	virtual LevelData* prepareLevel(Level*);
	virtual ChunkStorage* createChunkStorage(Dimension*);
	virtual void saveLevelData(LevelData&, std::vector<Player*>*);
	virtual bool_t load(Player*);
	virtual bool_t save(Player*);
	virtual void closeAll();
	virtual void saveGame(Level*);
	virtual void loadEntities(Level*, LevelChunk*);
	virtual LevelChunk* load(Level*, int32_t, int32_t);
	virtual void save(Level*, LevelChunk*);
	virtual void saveEntities(Level*, LevelChunk*);
	virtual void saveAll(Level*, std::vector<LevelChunk*>&);
	virtual void tick();
	virtual void flush();

};
