#pragma once
#include <tile/Tile.hpp>

struct TransparentTile : Tile{
	bool_t field_7C;
	byte field_7D, field_7E, field_7F;

	TransparentTile(int32_t, const std::string&, Material*);

	virtual ~TransparentTile();
	virtual bool_t shouldRenderFace(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
};
