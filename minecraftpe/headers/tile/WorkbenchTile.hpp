#pragma once
#include <tile/Tile.hpp>

struct WorkbenchTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8;

	WorkbenchTile(int32_t);

	virtual ~WorkbenchTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
};
