#pragma once
#include <tile/Tile.hpp>

struct FenceTile : Tile{
	bool_t connectsTo(struct LevelSource*, int32_t, int32_t, int32_t);

	FenceTile(int32_t id, const std::string&, Material*);

	virtual ~FenceTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
};
