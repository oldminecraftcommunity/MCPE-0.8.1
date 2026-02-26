#pragma once
#include <level/chunk/LevelChunk.hpp>

struct EmptyLevelChunk: LevelChunk
{
	EmptyLevelChunk(Level* level);
	virtual ~EmptyLevelChunk();
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
	virtual bool_t isSkyLit(int32_t, int32_t, int32_t);
	virtual void lightLava();
	virtual void recalcBlockLights();
	virtual void skyBrightnessChanged();
	virtual void load();
	virtual void unload();
	virtual void markUnsaved();
	virtual void getEntities(struct Entity*, const struct AABB&, std::vector<struct Entity*>&);
	virtual int32_t getTile(int32_t, int32_t, int32_t);
	virtual bool_t setTile(int32_t, int32_t, int32_t, int32_t);
	virtual bool_t setTileAndData(int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getData(int32_t, int32_t, int32_t);
	virtual bool_t setData(int32_t, int32_t, int32_t, int32_t);
	virtual void setBlocks(uint8_t*, int32_t);
	virtual int32_t getBlocksAndData(uint8_t*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t setBlocksAndData(uint8_t*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual Random getRandom(int32_t);
	virtual bool_t isEmpty();
};
