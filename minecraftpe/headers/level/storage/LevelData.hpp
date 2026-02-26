#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <RakNetTypes.h>
#include <entity/player/PlayerData.hpp>


struct LevelData{
	PlayerData playerData;
	int32_t field_2C, field_30, field_34, field_38;
	int32_t field_3C, field_40, field_44, field_48;
	int32_t field_4C, field_50;
	std::string levelName;
	int32_t seed;
	int32_t xSpawn, ySpawn, zSpawn;
	int32_t time;
	int32_t lastPlayed;
	int32_t sizeOnDisk;
	struct CompoundTag* playerTag;
	int32_t dimensionID;
	int32_t gameType;
	int32_t storageVersion;
	bool_t spawnMobs;
	byte align1, align2, align3;
	int32_t stopTime;
	int32_t generatorVersion;

	LevelData(struct CompoundTag*);
	LevelData(const LevelData&);
	LevelData(const struct LevelSettings&, const std::string&, int32_t);
	LevelData(void);
	struct CompoundTag* createTag(const std::vector<struct Player*>&);
	struct CompoundTag* createTag();
	int32_t getDimension();
	int32_t getGameType();
	int32_t getGeneratorVersion();
	int32_t getLastPlayed();
	std::string getLevelName();
	struct CompoundTag* getLoadedPlayerTag();
	int32_t getSeed();
	int32_t getSizeOnDisk();
	bool_t getSpawnMobs();
	int32_t getStorageVersion();
	void getTagData(const struct CompoundTag*);
	int32_t getTime();
	int32_t getXSpawn();
	int32_t getYSpawn();
	int32_t getZSpawn();
	LevelData& operator=(const LevelData&);
	void setDimension(int32_t);
	void setGameType(int32_t);
	void setGeneratorVersion(int32_t);
	void setLevelName(const std::string&);
	void setLoadedPlayerTag(struct CompoundTag*);
	void setLoadedPlayerTo(struct Player*);
	void setPlayerTag(struct CompoundTag*);
	void setSeed(int32_t); //long
	void setSizeOnDisk(int32_t); //long
	void setSpawn(int32_t, int32_t, int32_t);
	void setSpawnMobs(bool_t);
	void setStopTime(int32_t); //long
	void setStorageVersion(int32_t);
	void setTagData(struct CompoundTag*, struct CompoundTag*);
	void setTime(int32_t); //long
	void setXSpawn(int32_t);
	void setYSpawn(int32_t);
	void setZSpawn(int32_t);
	void v1_read(RakNet::BitStream&, int32_t);
	void v1_write(RakNet::BitStream&);
	~LevelData();
};
