#pragma once
#include <tile/Tile.hpp>

struct ReedTile : Tile{

	ReedTile(int32_t, const std::string&, Material*);

	virtual ~ReedTile();
	virtual bool_t onFertilized(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getRenderLayer();
	virtual bool_t canSurvive(Level*, int32_t, int32_t, int32_t);
};
