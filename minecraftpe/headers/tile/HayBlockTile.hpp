#pragma once
#include <tile/RotatedPillarTile.hpp>

struct HayBlockTile: RotatedPillarTile
{
	TextureUVCoordinateSet field_80, field_98;
	HayBlockTile(int32_t);
	virtual ~HayBlockTile();
	virtual TextureUVCoordinateSet* getDirTexture(int32_t, int32_t);
};
