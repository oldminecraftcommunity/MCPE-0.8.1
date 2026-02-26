#pragma once
#include <_types.h>
#include <level/LevelSource.hpp>
#include <level/AdventureSettings.hpp>
#include <vector>
#include <map>
#include <set>
#include <util/Random.hpp>
#include <entity/particles/ParticleType.hpp>
#include <string>
#include <util/Color4.hpp>
#include <math/AABB.hpp>
#include <math/Pos.hpp>
#include <level/biome/Biome.hpp>
#include <util/TilePos.hpp>
#include <level/storage/LevelData.hpp>
#include <util/ChunkPos.hpp>
#include <level/LightUpdate.hpp>

struct LevelStorage;
struct Dimension;
struct LevelSettings;
struct ChunkSource;
struct TickNextTickData;
struct TileEntity;
struct _TickPtr;
struct PRInfo;
struct Particle;
struct Level : LevelSource{
	std::vector<AABB> aabbVec;
	bool_t instantTick;
	bool_t isClientMaybe;
	int8_t field_12, field_13;
	int32_t difficulty;
	AdventureSettings adventureSettings;
	byte field_1e, field_1f; //1e, 1f - align
	std::vector<struct Entity*> entities;
	std::map<int32_t, struct Entity*> eid2entity; //TODO check type
	std::vector<TileEntity*> tileEntities;
	std::vector<TileEntity*> field_50;
	int8_t field_5C, field_5D, field_5E, field_5F;
	std::vector<struct Player*> playersMaybe;
	int32_t skyDarken;
	Dimension* dimensionPtr;
	struct RakNetInstance* rakNetInstance;
	Random random;
	int8_t field_A48, field_A49, field_A4A, field_A4B;
	std::vector<struct LevelListener*> levelListeners;
	ChunkSource* chunkSource;
	LevelStorage* levelStoragePtr;
	LevelData levelData;
	int8_t field_AF0;
	int8_t spawnAnimalsMaybe;
	int8_t spawnMonstersMaybe;
	int8_t field_AF3;
	int32_t prevRandomNumber;
	int32_t constRandom;
	std::vector<struct Entity*> entVec;
	std::set<TickNextTickData> tickDataTreeImpl;
	std::set<ChunkPos> somethingRelatedToChunkPos;
	std::vector<LightUpdate> lightsToUpdate;
	std::map<int32_t, struct Entity*> eid2entity2;
	int8_t _updateLights;
	int8_t field_B5D, field_B5E, field_B5F;
	int32_t lightUpdatesCnt;
	int8_t field_B64, nightMode, field_B66, field_B67;
	double field_B64_;
	std::vector<PRInfo> field_B6C;
	int32_t prevTimeSent;
	std::set<_TickPtr*> tickPtrSetImpl;
	std::vector<Entity*> field_B94; //TODO check type

	Level(struct LevelStorage*, const std::string&, const LevelSettings&, bool_t, int32_t, struct Dimension*);
	void _init(const std::string&, const LevelSettings&, int32_t, struct Dimension*);
	void _syncTime(int32_t); //long
	bool_t addEntity(struct Entity*);
	void addListener(struct LevelListener*);
	Particle * addParticle(ParticleType, float, float, float, float, float, float, int32_t);
	void animateTick(int32_t, int32_t, int32_t);
	void broadcastEntityEvent(struct Entity*, char_t);
	bool_t canSeeSky(int32_t, int32_t, int32_t);
	bool_t checkAndHandleWater(const struct AABB&, const struct Material*, struct Entity*);
	HitResult clip(const Vec3&, const Vec3&, bool_t, bool_t);
	bool_t containsAnyLiquid(const struct AABB&);
	bool_t containsFireTile(const struct AABB&);
	bool_t containsLiquid(const struct AABB&, const struct Material*);
	bool_t containsMaterial(const struct AABB&, const struct Material*);
	int32_t countInstanceOfBaseType(int32_t);
	int32_t countInstanceOfType(int32_t);
	void dispatchEntityData(struct Entity*);
	void entityAdded(struct Entity*);
	void entityRemoved(struct Entity*);
	void explode(struct Entity*, float, float, float, float);
	void explode(struct Entity*, float, float, float, float, bool_t);
	void extinguishFire(int32_t, int32_t, int32_t, int32_t);
	struct Path* findPath(struct Entity*, struct Entity*, float, bool_t, bool_t, bool_t, bool_t);
	struct Path* findPath(struct Entity*, int32_t, int32_t, int32_t, float, bool_t, bool_t, bool_t, bool_t);
	std::vector<struct Entity*>* getAllEntities();
	struct BiomeSource* getBiomeSource();
	int32_t getBrightness(const struct LightLayer&, int32_t, int32_t, int32_t);
	struct LevelChunk* getChunk(int32_t, int32_t);
	struct LevelChunk* getChunkAt(int32_t, int32_t);
	struct ChunkSource* getChunkSource();
	Color4 getCloudColor(float);
	std::vector<AABB>* getCubes(const struct Entity*, const AABB&, float*);
	int32_t getDirectSignal(int32_t, int32_t, int32_t, int32_t);
	std::vector<struct Entity*>* getEntities(struct Entity*, const AABB&);
	int32_t getEntitiesOfClass(int32_t, const AABB&, std::vector<struct Entity*>&);
	int32_t getEntitiesOfType(int32_t, const AABB&, std::vector<struct Entity*>&);
	struct Entity* getEntity(int32_t);
	Color4 getFogColor(float);
	int32_t getHeightmap(int32_t, int32_t);
	struct LevelData* getLevelData();
	struct LevelStorage* getLevelStorage();
	int32_t getLightDepth(int32_t, int32_t);
	int32_t getLightsToUpdate();
	struct Mob* getMob(int32_t);
	int32_t getMoonPhase();
	struct Player* getNearestPlayer(struct Entity*, float);
	struct Player* getNearestPlayer(float, float, float, float);
	struct Player* getPlayer(const std::string&);

	/*returns <player_count>:PlayerName,PlayerName2, ...
	segfaults(at least in x86 build) after it was called 9 times, 8th time will have corrupted string
	code used for testing:

	void* level_getPlayerNames = internal_dlsym(handle, "_ZN5Level14getPlayerNamesEv");
	int player = *(int*)(((int)ninecraft_app) + 3168);
	if(player){
		int level = *(int*)(player+64);
		if(level){
			std_string str;
			(((void (*)(std_string*, int)) level_getPlayerNames))(&str, level);
			printf("%s\n", std_string_cstr(&str));
		}
	}
	According to 0.7.2 it uses std::basic_stringstream and std::ostream
	According to 0.8.1 x86 it uses std::ios std::stringbuf std::streambuf and stuff like this
	Doesnt seem to be used by anything in 0.8
	*/
	std::string getPlayerNames();

	Biome::MobSpawnerData getRandomMobSpawnAt(const MobCategory&, int32_t, int32_t, int32_t);
	int32_t getRawBrightness(int32_t, int32_t, int32_t);
	int32_t getRawBrightness(int32_t, int32_t, int32_t, bool_t);
	int32_t getSeaLevel();
	int32_t getSeed();
	float getSeenPercent(const Vec3&, const AABB&);
	TilePos getSharedSpawnPos();
	int32_t getSignal(int32_t, int32_t, int32_t, int32_t);
	Color4 getSkyColor(struct Entity*, float);
	Color4 getSkyColor(int32_t, int32_t, float);
	int32_t getSkyDarken(float);
	float getStarBrightness(float);
	float getSunAngle(float);
	float getSunIntensity(float, struct Mob*, float);
	Vec3 getSunlightDirection(float);
	Color4 getSunriseColor(float);
	std::vector<AABB> getTileCubes(const AABB&);
	int32_t getTileCubesCount(const AABB&);
	struct TileEntity* getTileEntity(int32_t, int32_t, int32_t);
	bool_t getTileObstructsChests(int32_t, int32_t, int32_t);
	int32_t getTime();
	float getTimeOfDay(float);
	int32_t getTopSolidBlock(int32_t, int32_t);
	int32_t getTopTile(int32_t, int32_t);
	int32_t getTopTileY(int32_t, int32_t);
	bool_t hasChunk(int32_t, int32_t);
	bool_t hasChunkAt(int32_t, int32_t, int32_t);
	bool_t hasChunksAt(int32_t, int32_t, int32_t, int32_t);
	bool_t hasChunksAt(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	bool_t hasDirectSignal(int32_t, int32_t, int32_t);
	bool_t hasNeighborSignal(int32_t, int32_t, int32_t);
	bool_t inRange(int32_t, int32_t, int32_t);
	bool_t isDay();
	bool_t isNightMode();
	bool_t isSkyLit(int32_t, int32_t, int32_t);
	bool_t isTopSolidBlocking(struct Tile*, int32_t);
	bool_t isTopSolidBlocking(int32_t, int32_t, int32_t);
	bool_t isUnobstructed(const AABB&);
	void levelEvent(struct Player*, int32_t, int32_t, int32_t, int32_t, int32_t);
	void levelEvent(int32_t, int32_t, int32_t, int32_t, int32_t);
	void lightColumnChanged(int32_t, int32_t, int32_t, int32_t);
	void loadEntities();
	void loadPlayer(struct Player*, bool_t);
	bool_t mayInteract(struct Player*, int32_t, int32_t, int32_t);
	bool_t mayPlace(int32_t, int32_t, int32_t, int32_t, bool_t, uint8_t); //uchar
	void neighborChanged(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void playSound(struct Entity*, const std::string&, float, float);
	void playSound(float, float, float, const std::string&, float, float);
	void prepare();
	void registerTemporaryPointer(struct _TickPtr*);
	void removeEntity(struct Entity*);
	void removeListener(struct LevelListener*);
	void removePlayer(struct Player*);
	void removeTile(int32_t, int32_t, int32_t);
	void removeTileEntity(int32_t, int32_t, int32_t);
	void saveGame();
	void saveLevelData();
	void savePlayers();
	void sendTileUpdated(int32_t, int32_t, int32_t);
	void setBrightness(const struct LightLayer&, int32_t, int32_t, int32_t, int32_t);
	bool_t setData(int32_t, int32_t, int32_t, int32_t, int32_t);
	bool_t setDataAndUpdate(int32_t, int32_t, int32_t, int32_t);
	bool_t setDataNoUpdate(int32_t, int32_t, int32_t, int32_t);
	void setDayCycleActive(bool_t);
	void setInitialSpawn(void);
	void setNightMode(bool_t);
	void setSpawnPos(Pos);
	void setSpawnSettings(bool_t, bool_t);
	bool_t setTile(int32_t, int32_t, int32_t, int32_t, int32_t);
	bool_t setTileAndData(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	bool_t setTileAndDataNoUpdate(int32_t, int32_t, int32_t, int32_t, int32_t);
	void setTileDirty(int32_t, int32_t, int32_t);
	void setTileEntity(int32_t, int32_t, int32_t, struct TileEntity*);
	bool_t setTileNoUpdate(int32_t, int32_t, int32_t, int32_t);
	void setTilesDirty(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	int32_t setTime(int32_t); //long
	void setUpdateLights(bool_t);
	void setZombieAi(std::vector<struct Zombie*>&);
	void swap(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void takePicture(struct TripodCamera*, struct Entity*);
	void tick(struct Entity*);
	void tick(struct Entity*, bool_t);
	void tickEntities();
	void tickTemporaryPointers();
	void tileEntityChanged(int32_t, int32_t, int32_t, struct TileEntity*);
	void tileEvent(int32_t, int32_t, int32_t, int32_t, int32_t);
	void tileUpdated(int32_t, int32_t, int32_t, int32_t);
	void unregisterTemporaryPointer(struct _TickPtr*);
	void updateLight(const struct LightLayer&, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void updateLight(const struct LightLayer&, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, bool_t);
	void updateLightIfOtherThan(const struct LightLayer&, int32_t, int32_t, int32_t, int32_t);
	bool_t updateLights();
	void updateNeighborsAt(int32_t, int32_t, int32_t, int32_t);
	bool_t updateSkyBrightness();
	void updateSkyDarken();
	void validateSpawn();

	//woah vt is so smol ty mojang <3
	virtual ~Level();
	virtual int32_t getTile(int32_t, int32_t, int32_t);
	virtual bool_t isEmptyTile(int32_t, int32_t, int32_t);
	virtual float getBrightness(int32_t, int32_t, int32_t);
	virtual int32_t getData(int32_t, int32_t, int32_t);
	virtual struct Material* getMaterial(int32_t, int32_t, int32_t);
	virtual bool_t isSolidRenderTile(int32_t, int32_t, int32_t);
	virtual bool_t isSolidBlockingTile(int32_t, int32_t, int32_t);
	virtual struct Biome* getBiome(int32_t, int32_t);
	virtual void tick();
	virtual bool_t tickPendingTicks(bool_t);
	virtual void addToTickNextTick(int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void updateSleepingPlayerList();
	virtual struct ChunkSource* createChunkSource();
	virtual void tickTiles();
};
