#pragma once
#include <tile/Bush.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

struct CropTile : Bush{
	TextureAtlasTextureItem texture2;

	CropTile(int32_t, const std::string&);
	float getGrowthSpeed(Level*, int32_t, int32_t, int32_t);

	virtual ~CropTile() {
	}
	virtual bool_t onFertilized(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t data = level->getData(x, y, z);
		int32_t v9 = level->random.genrand_int32() % 3 + data + 2;
		if (v9 >= 7) v9 = 7;

		level->setData(x, y, z, v9, 2);
		return 1;
	}
	virtual int32_t getRenderShape();
	virtual const TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual const TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual void spawnResources(Level*, int32_t x, int32_t, int32_t, int32_t, float);
	virtual bool_t mayPlaceOn(int32_t);
	virtual struct Item* getBaseSeed();
	virtual int32_t getBasePlantId();
};
