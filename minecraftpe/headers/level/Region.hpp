#pragma once
#include <level/LevelSource.hpp>

struct Region: LevelSource
{
	int32_t minCX, minCZ;
	struct LevelChunk*** chunks;
	struct Level* level;
	int32_t sizeX, sizeZ;

	Region(struct Level* level, int32_t minX, int32_t minY, int32_t minZ, int32_t maxX, int32_t maxY, int32_t maxZ);
	int32_t getRawBrightness(int32_t x, int32_t y, int32_t z);
	int32_t getRawBrightness(int32_t x, int32_t y, int32_t z, bool_t complex);
	~Region();

	virtual int32_t getTile(int32_t, int32_t, int32_t);
	virtual bool_t isEmptyTile(int32_t, int32_t, int32_t);
	virtual float getBrightness(int32_t, int32_t, int32_t);
	virtual int32_t getData(int32_t, int32_t, int32_t);
	virtual Material* getMaterial(int32_t, int32_t, int32_t);
	virtual bool_t isSolidRenderTile(int32_t, int32_t, int32_t);
	virtual bool_t isSolidBlockingTile(int32_t, int32_t, int32_t);
	virtual Biome* getBiome(int32_t, int32_t);
};
