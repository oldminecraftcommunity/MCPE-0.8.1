#pragma once
#include <tile/CropTile.hpp>

struct PotatoTile: CropTile
{
	TextureAtlasTextureItem field_AC;

	PotatoTile(int32_t);

	virtual ~PotatoTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual void spawnResources(Level*, int32_t, int32_t, int32_t, int32_t, float);
	virtual struct Item* getBaseSeed();
	virtual int32_t getBasePlantId();
};
