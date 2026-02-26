#pragma once
#include <_types.h>

struct Material;
struct Biome;

struct LevelSource{
	virtual ~LevelSource();
	virtual int32_t getTile(int32_t, int32_t, int32_t) = 0;
	virtual bool_t isEmptyTile(int32_t, int32_t, int32_t) = 0;
	virtual float getBrightness(int32_t, int32_t, int32_t) = 0;
	virtual int32_t getData(int32_t, int32_t, int32_t) = 0;
	virtual Material* getMaterial(int32_t, int32_t, int32_t) = 0;
	virtual bool_t isSolidRenderTile(int32_t, int32_t, int32_t) = 0;
	virtual bool_t isSolidBlockingTile(int32_t, int32_t, int32_t) = 0;
	virtual Biome* getBiome(int32_t, int32_t) = 0;
};
