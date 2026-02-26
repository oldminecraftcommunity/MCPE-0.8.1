#pragma once
#include <tile/Tile.hpp>

struct TrapDoorTile : Tile{
	TrapDoorTile(int32_t, const struct Material*);

	void _setShape(int32_t);
	static bool_t attachesTo(int32_t);
	bool_t blocksLight(void);
	int32_t getDir(int32_t);
	static bool_t isOpen(int32_t);
	void setOpen(Level*, int32_t, int32_t, int32_t, bool_t);

	virtual ~TrapDoorTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual void updateDefaultShape();
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual AABB getTileAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t, uint8_t);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual HitResult clip(Level*, int32_t, int32_t, int32_t, const Vec3&, const Vec3&);
	virtual int32_t getRenderLayer();
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
	virtual void attack(Level*, int32_t, int32_t, int32_t, Player*);

};
