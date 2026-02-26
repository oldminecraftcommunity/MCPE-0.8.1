#pragma once
#include <_types.h>
#include <level/storage/DataLayer.hpp>
#include <vector>
#include <unordered_map>
#include <util/TilePos.hpp>
#include <util/Random.hpp>

struct LevelChunk
{
	static bool_t touchedSky;
	int32_t field_4;
	bool_t loaded;
	int8_t field_9, field_A, field_B;
	struct Level* level;
	DataLayer tileMeta, skyLight, blockLight;
	int8_t heightMap[256];
	int8_t updateMap[256];
	int32_t topBlockY;
	int32_t chunkX, chunkZ;
	int32_t chunkXworld, chunkZworld;
	int8_t decorated;
	bool_t unsaved;
	int8_t field_24A, field_24B, field_24C, field_24D, field_24E, field_24F;
	int32_t field_250;
	uint8_t* tiles;
	int8_t field_258, field_259, field_25A, field_25B;
	std::vector<struct Entity*> miniChunkEntities[8];
	std::unordered_map<TilePos, struct TileEntity*> tileEntities;

	LevelChunk(struct Level*, int32_t, int32_t);
	LevelChunk(struct Level*, uint8_t*, int32_t, int32_t);
	void addTileEntity(struct TileEntity*);
	void clearUpdateMap();
	void deleteBlockData();
	struct TileEntity* getTileEntity(int32_t, int32_t, int32_t);
	std::unordered_map<TilePos, struct TileEntity*>* getTileEntityMap();
	bool_t hasTileEntityAt(struct TileEntity*);
	bool_t hasTileEntityAt(int32_t, int32_t, int32_t);
	void init();
	void lightGap(int32_t, int32_t, int32_t);
	void lightGaps(int32_t, int32_t);
	void recalcHeight(int32_t, int32_t, int32_t);
	void removeTileEntity(int32_t, int32_t, int32_t);
	void setTileEntity(int32_t, int32_t, int32_t, struct TileEntity*);
	void setTileRaw(int32_t, int32_t, int32_t, int32_t);


	virtual ~LevelChunk();
	virtual bool_t isAt(int32_t, int32_t);
	virtual int32_t getHeightmap(int32_t, int32_t);
	virtual void recalcHeightmap();
	virtual void recalcHeightmapOnly();
	virtual int32_t getBrightness(const struct LightLayer&, int32_t, int32_t, int32_t);
	virtual void setBrightness(const struct LightLayer&, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getRawBrightness(int32_t, int32_t, int32_t, int32_t);
	virtual void addEntity(struct Entity*);
	virtual void removeEntity(struct Entity*);
	virtual void removeEntity(struct Entity*, int32_t);
	virtual void getEntitiesOfClass(int32_t, const struct AABB&, std::vector<struct Entity*>&);
	virtual void getEntitiesOfType(int32_t, const struct AABB&, std::vector<struct Entity*>&);
	virtual bool_t isSkyLit(int32_t, int32_t, int32_t);
	virtual void lightLava();
	virtual void recalcBlockLights();
	virtual void skyBrightnessChanged();
	virtual void load();
	virtual void unload();
	virtual bool_t shouldSave(bool_t);
	virtual void markUnsaved();
	virtual int32_t countEntities();
	virtual void getEntities(struct Entity*, const struct AABB&, std::vector<struct Entity*>&);
	virtual int32_t getTile(int32_t, int32_t, int32_t);
	virtual bool_t setTile(int32_t, int32_t, int32_t, int32_t);
	virtual bool_t setTileAndData(int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getData(int32_t, int32_t, int32_t);
	virtual bool_t setData(int32_t, int32_t, int32_t, int32_t);
	virtual void setBlocks(uint8_t*, int32_t);
	virtual int32_t getBlocksAndData(uint8_t*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t setBlocksAndData(uint8_t*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual Random getRandom(int32_t); //long
	virtual bool_t isEmpty();
};
