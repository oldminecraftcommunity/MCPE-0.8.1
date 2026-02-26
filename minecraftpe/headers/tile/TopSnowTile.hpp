#pragma once
#include <tile/Tile.hpp>

struct TopSnowTile : Tile{
	TopSnowTile(int32_t, const std::string&, Material*);
	bool_t checkCanSurvive(Level*, int32_t, int32_t, int32_t);


	virtual ~TopSnowTile();
	virtual int32_t getTileType();
	virtual bool_t isCubeShaped();
	virtual bool_t shouldRenderFace(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual float getThickness();
	virtual void playerDestroy(Level*, Player*, int32_t, int32_t, int32_t, int32_t);

};
