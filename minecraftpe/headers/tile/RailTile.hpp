#pragma once
#include <tile/BaseRailTile.hpp>

struct RailTile : BaseRailTile{
	TextureUVCoordinateSet field_84;

	RailTile(int32_t);

	virtual ~RailTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual void updateState(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
};
