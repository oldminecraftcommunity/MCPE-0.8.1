#pragma once
#include <tile/Tile.hpp>

struct FarmTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0;

	FarmTile(int32_t);


	virtual ~FarmTile();
	virtual bool_t isCubeShaped();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual void fallOn(Level*, int32_t, int32_t, int32_t, Entity*, float);
};
