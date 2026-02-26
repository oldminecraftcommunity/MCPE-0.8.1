#pragma once
#include <tile/EntityTile.hpp>
#include <util/Random.hpp>

struct ChestTile : EntityTile{
	Random random;
	TextureUVCoordinateSet field_A50, field_A68, field_A80;

	ChestTile(int32_t);

	virtual ~ChestTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual int32_t getTileEntityType();
	virtual void onRemove(Level*, int32_t, int32_t, int32_t);
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, struct Mob*, int32_t);
};
