#pragma once
#include <tile/Tile.hpp>

struct MelonTile : Tile{
	TextureUVCoordinateSet field_7C, field_94;

	MelonTile(int32_t);

	virtual ~MelonTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);

};
