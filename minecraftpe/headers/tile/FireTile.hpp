#pragma once
#include <tile/Tile.hpp>

struct FireTile : Tile{
	int32_t flammability[256];
	int32_t field_480[256];

	FireTile(int32_t, const std::string&);
	bool_t canBurn(struct LevelSource*, int32_t, int32_t, int32_t);
	void checkBurn(Level*, int32_t, int32_t, int32_t, int32_t, Random*);
	int32_t getFireOdds(Level*, int32_t, int32_t, int32_t);
	int32_t getFlammability(Level*, int32_t, int32_t, int32_t, int32_t);
	bool_t isValidFireLocation(Level*, int32_t, int32_t, int32_t);


	virtual ~FireTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPick();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getTickDelay();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void animateTick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getResourceCount(Random*);
	virtual int32_t getRenderLayer();
};
