#pragma once
#include <tile/MultiTextureTile.hpp>

struct SandStoneTile : MultiTextureTile{
	TextureUVCoordinateSet field_B0, field_C8;

	SandStoneTile(int32_t, const std::string&);

	virtual ~SandStoneTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
};
