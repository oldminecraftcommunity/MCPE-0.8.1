#pragma once
#include <tile/entity/TileEntity.hpp>
#include <item/ItemInstance.hpp>

struct NetherReactorTileEntity: TileEntity
{
	bool_t isInitialized, hasFinished;
	int8_t field_5E, field_5F;
	int32_t field_60;
	int16_t progress;
	int16_t field_66;

	ItemInstance GetLowOddsSpawnItem();
	NetherReactorTileEntity();
	void buildCrockedRoofVolume(bool_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void buildDome(int32_t x, int32_t y, int32_t z);
	void buildFloorVolume(int32_t x, int32_t y, int32_t z, int32_t r, int32_t h, int32_t id);
	void buildHollowedVolume(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	bool_t checkLevelChange(int32_t);
	void clearDomeSpace(int32_t x, int32_t y, int32_t z);
	void deterioateCrockedRoofVolume(bool_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void deterioateDome(int32_t, int32_t, int32_t);
	void deterioateHollowedVolume(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void finishReactorRun();
	std::string getName();
	int32_t getNumEnemiesPerLevel(int32_t);
	int32_t getNumItemsPerLevel(int32_t);
	ItemInstance getSpawnItem();
	Vec3 getSpawnPosition(float, float, float);
	bool_t isEdge(int32_t x, int32_t y, int32_t z);
	void killPigZombies();
	void lightItUp(int32_t x, int32_t y, int32_t z);
	int32_t numOfFreeEnemySlots();
	bool_t playersAreCloseBy();
	void spawnEnemy();
	void spawnItem();
	void spawnItems(int32_t cnt);
	void tickGlowingRedstoneTransformation(int32_t);
	void trySpawnPigZombies(int32_t, int32_t);
	void turnGlowingObsidianLayerToObsidian(int32_t);
	void turnLayerToGlowingObsidian(int32_t, int32_t);

	virtual ~NetherReactorTileEntity();
	virtual bool_t shouldSave();
	virtual void load(CompoundTag*);
	virtual bool_t save(CompoundTag*);
	virtual void tick();
};
