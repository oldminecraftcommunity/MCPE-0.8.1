#pragma once
#include <tile/Tile.hpp>

struct TorchTile : Tile{
	bool_t isConnection(Level*, int32_t, int32_t, int32_t);
	bool_t checkCanSurvive(Level*, int32_t, int32_t, int32_t);

	TorchTile(int32_t, const std::string&, Material*);
	virtual ~TorchTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void animateTick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);
	virtual HitResult clip(Level*, int32_t, int32_t, int32_t, const Vec3&, const Vec3&);
	virtual int32_t getRenderLayer();
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
};
