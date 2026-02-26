#pragma once
#include <tile/Tile.hpp>

struct FenceGateTile : Tile{
	FenceGateTile(int32_t id, const std::string&, Material* mat);
	virtual ~FenceGateTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
};
