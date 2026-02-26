#pragma once
#include <tile/BaseRailTile.hpp>

struct PoweredRailTile : BaseRailTile{
	TextureUVCoordinateSet poweredRailTexture;

	PoweredRailTile(int32_t);
	bool_t findPoweredRailSignal(Level*, int32_t, int32_t, int32_t, bool_t, int32_t, int32_t);
	bool_t isSameRailWithPower(Level*, int32_t, int32_t, int32_t, int32_t, bool_t, int32_t);

	virtual ~PoweredRailTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t);
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual void updateState(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
};
