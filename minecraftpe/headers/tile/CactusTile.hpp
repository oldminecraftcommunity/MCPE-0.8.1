#pragma once
#include <tile/Tile.hpp>

struct CactusTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0;

	CactusTile(int32_t);

	virtual ~CactusTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual AABB getTileAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getRenderLayer();
	virtual void entityInside(Level*, int32_t, int32_t, int32_t, Entity*);
	virtual bool_t canSurvive(Level*, int32_t, int32_t, int32_t);
};
