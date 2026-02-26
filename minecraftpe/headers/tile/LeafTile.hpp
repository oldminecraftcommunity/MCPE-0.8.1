#pragma once
#include <tile/TransparentTile.hpp>

struct LeafTile : TransparentTile{
	int32_t* treeBlocksNearby;
	bool_t field_88;
	int8_t field_89, field_8A, field_8B;
	TextureUVCoordinateSet field_8C[4];
	TextureUVCoordinateSet field_EC[4];
	TextureUVCoordinateSet field_14C[4];
	int32_t field_1AC, field_1B0, field_1B4, field_1B8, field_1BC, field_1C0;

	LeafTile(int32_t, const std::string&);

	virtual ~LeafTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual TextureUVCoordinateSet* getCarriedTexture(int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void onRemove(Level*, int32_t, int32_t, int32_t);
	virtual void onGraphicsModeChanged(bool_t a2);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual void spawnResources(Level*, int32_t, int32_t, int32_t, int32_t, float);
	virtual int32_t getRenderLayer();
	virtual int32_t getColor(LevelSource*, int32_t, int32_t, int32_t);
	virtual void playerDestroy(Level*, Player*, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
