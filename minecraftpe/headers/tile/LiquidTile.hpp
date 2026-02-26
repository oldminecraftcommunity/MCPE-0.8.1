#pragma once
#include <tile/Tile.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

struct LiquidTile : Tile{
	TextureUVCoordinateSet field_7C, field_94;
	TextureAtlasTextureItem field_AC;

	LiquidTile(int32_t, const struct Material*, const std::string&, const std::string&);
	void _trySpreadFire(struct Level*, int32_t, int32_t, int32_t, struct Random*);
	void fizz(struct Level*, int32_t, int32_t, int32_t);
	int32_t getDepth(struct Level*, int32_t, int32_t, int32_t);
	Vec3 getFlow(LevelSource*, int32_t, int32_t, int32_t);
	int32_t getRenderedDepth(struct LevelSource*, int32_t, int32_t, int32_t);
	static float getSlopeAngle(LevelSource*, int32_t, int32_t, int32_t, const struct Material*);
	void updateLiquid(Level*, int32_t, int32_t, int32_t);

	virtual ~LiquidTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual float getBrightness(LevelSource*, int32_t, int32_t, int32_t);
	virtual bool_t shouldRenderFace(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t isLiquidTile();
	virtual bool_t mayPick(int32_t, bool_t);
	virtual int32_t getTickDelay();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void animateTick(struct Level*, int32_t, int32_t, int32_t, struct Random*);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual int32_t getRenderLayer();
	virtual void handleEntityInside(Level*, int32_t, int32_t, int32_t, Entity*, Vec3&);
	virtual int32_t getColor(LevelSource*, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTextureNum(int32_t);
};
