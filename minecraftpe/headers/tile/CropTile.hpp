#pragma once
#include <tile/Bush.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

struct CropTile : Bush{
	TextureAtlasTextureItem texture2;

	CropTile(int32_t, const std::string&);
	float getGrowthSpeed(Level*, int32_t, int32_t, int32_t);

	virtual ~CropTile();
	virtual bool_t onFertilized(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getRenderShape();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual void spawnResources(Level*, int32_t, int32_t, int32_t, int32_t, float);
	virtual bool_t mayPlaceOn(int32_t);
	virtual struct Item* getBaseSeed();
	virtual int32_t getBasePlantId();
};
