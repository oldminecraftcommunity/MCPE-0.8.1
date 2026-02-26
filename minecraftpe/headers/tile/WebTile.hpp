#pragma once
#include <tile/Tile.hpp>

struct WebTile : Tile{
	WebTile(int32_t, const std::string&, Material*);

	virtual ~WebTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getRenderLayer();
	virtual void entityInside(Level*, int32_t, int32_t, int32_t, Entity*);

};
