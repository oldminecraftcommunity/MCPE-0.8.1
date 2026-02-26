#pragma once
#include <tile/EntityTile.hpp>
#include <util/Random.hpp>
#include <rendering/TextureUVCoordinateSet.hpp>

struct FurnaceTile : EntityTile{
	static bool_t noDrop;

	Random rand;
	bool_t isLit;
	int8_t field_A4D, field_A4E, field_A4F;
	TextureUVCoordinateSet field_A50, field_A68, field_A80, field_A98;

	FurnaceTile(int32_t, bool_t);
	static void setLit(bool_t, Level*, int32_t, int32_t, int32_t);

	virtual ~FurnaceTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getTileEntityType();
	virtual void animateTick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void onRemove(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
};
