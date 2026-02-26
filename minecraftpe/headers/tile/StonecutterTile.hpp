#pragma once
#include <tile/Tile.hpp>

struct StonecutterTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8;

	StonecutterTile(int32_t);

	virtual ~StonecutterTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);

};
