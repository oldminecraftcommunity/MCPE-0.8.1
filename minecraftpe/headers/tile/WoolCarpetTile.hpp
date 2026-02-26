#pragma once
#include <tile/Tile.hpp>

struct WoolCarpetTile : Tile{
	WoolCarpetTile(int32_t);
	bool_t checkCanSurvive(Level*, int32_t, int32_t, int32_t);
	static int32_t getItemAuxValueForTileData(int32_t);
	static int32_t getTileDataForItemAuxValue(int32_t);
	void updateShape(int32_t);


	virtual ~WoolCarpetTile();
	virtual bool_t isCubeShaped();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual void updateDefaultShape();
	virtual bool_t shouldRenderFace(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual float getThickness();
	virtual bool_t canSurvive(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
