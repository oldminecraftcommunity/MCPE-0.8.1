#pragma once
#include <tile/Tile.hpp>

struct StairTile : Tile{
	Tile* block;
	int8_t field_84, field_85, field_86, field_87;
	int32_t field_88, meta;
	static int DEAD_SPACES[8][2];
	StairTile(int32_t, Tile*, int32_t);
	static bool_t isLockAttached(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	static bool_t isStairs(int32_t);
	void setBaseShape(LevelSource*, int32_t, int32_t, int32_t);
	bool_t setInnerPieceShape(LevelSource*, int32_t, int32_t, int32_t);
	bool_t setStepShape(LevelSource*, int32_t, int32_t, int32_t);

	virtual ~StairTile();
	virtual int32_t getTileType();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual void addLights(Level*, int32_t, int32_t, int32_t);
	virtual float getBrightness(LevelSource*, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual void addAABBs(Level*, int32_t, int32_t, int32_t, const AABB*, std::vector<AABB>&);
	virtual AABB getTileAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPick();
	virtual bool_t mayPick(int32_t, bool_t);
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t, uint8_t);
	virtual int32_t getTickDelay();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void animateTick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void destroy(Level*, int32_t, int32_t, int32_t, int32_t);
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);
	virtual void onRemove(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getResourceCount(Random*);
	virtual float getExplosionResistance(Entity*);
	virtual HitResult clip(Level*, int32_t, int32_t, int32_t, const Vec3&, const Vec3&);
	virtual void wasExploded(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getRenderLayer();
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
	virtual void stepOn(Level*, int32_t, int32_t, int32_t, Entity*);
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
	virtual void prepareRender(Level*, int32_t, int32_t, int32_t);
	virtual void attack(Level*, int32_t, int32_t, int32_t, Player*);
	virtual void handleEntityInside(Level*, int32_t, int32_t, int32_t, Entity*, Vec3&);
};
