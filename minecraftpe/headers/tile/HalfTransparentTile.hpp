#pragma once
#include <tile/Tile.hpp>

struct HalfTransparentTile : Tile{
	bool_t field_80;

	HalfTransparentTile(int32_t id, const std::string& s, Material* m);
	virtual ~HalfTransparentTile();
	virtual bool_t shouldRenderFace(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual int32_t getRenderLayer();
};
