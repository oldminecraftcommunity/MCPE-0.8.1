#pragma once
#include <tile/EntityTile.hpp>

struct SignTile : EntityTile{
	bool_t field_80;
	byte field_81, field_82, field_83;

	SignTile(int32_t, bool_t);

	virtual ~SignTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual AABB getTileAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t isPathfindable(LevelSource*, int32_t, int32_t, int32_t);
	virtual int32_t getTileEntityType();
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);

};
