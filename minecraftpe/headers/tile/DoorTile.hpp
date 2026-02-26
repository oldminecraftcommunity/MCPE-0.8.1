#pragma once
#include <tile/Tile.hpp>

struct DoorTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8;

	DoorTile(int32_t, const struct Material*);
	bool_t blocksLight();
	static int32_t getCompositeData(struct LevelSource*, int32_t, int32_t, int32_t);
	static int32_t getDir(struct LevelSource*, int32_t, int32_t, int32_t);
	static bool_t isOpen(struct LevelSource*, int32_t, int32_t, int32_t);
	static void setOpen(Level*, int32_t, int32_t, int32_t, bool_t);

	virtual ~DoorTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual AABB getTileAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual void playerWillDestroy(Level*, int32_t, int32_t, int32_t, int32_t, Player*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual HitResult clip(Level*, int32_t, int32_t, int32_t, const Vec3&, const Vec3&);
	virtual int32_t getRenderLayer();
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
	virtual void attack(Level*, int32_t, int32_t, int32_t, Player*);
};
