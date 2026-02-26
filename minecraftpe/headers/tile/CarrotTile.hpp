#pragma once
#include <tile/CropTile.hpp>

struct CarrotTile : CropTile{
	TextureAtlasTextureItem field_AC;

	CarrotTile(int32_t);

	virtual ~CarrotTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual void spawnResources(Level*, int32_t, int32_t, int32_t, int32_t, float);
	virtual int32_t getBasePlantId();
	virtual struct Item* getBaseSeed();
};
