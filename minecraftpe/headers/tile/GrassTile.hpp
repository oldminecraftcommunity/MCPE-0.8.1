#pragma once
#include <tile/Tile.hpp>

struct GrassTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8, field_E0;

	GrassTile(int32_t);
	bool_t _randomWalk(Level*, int32_t&, int32_t&, int32_t&, int32_t);

	virtual ~GrassTile();
	virtual bool_t onFertilized(Level*, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual TextureUVCoordinateSet* getCarriedTexture(int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getColor(int32_t);
	virtual int32_t getColor(LevelSource*, int32_t, int32_t, int32_t);
};
