#pragma once
#include <tile/CropTile.hpp>

struct BeetrootTile : CropTile{
	TextureAtlasTextureItem texture3;

	BeetrootTile(int32_t);
	void spawnItem(Level*, int32_t, int32_t, int32_t, const struct ItemInstance&);

	virtual ~BeetrootTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual void spawnResources(Level*, int32_t, int32_t, int32_t, int32_t, float);
	virtual struct Item* getBaseSeed();
	virtual int32_t getBasePlantId();
};
