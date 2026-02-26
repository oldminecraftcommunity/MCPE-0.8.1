#pragma once
#include <_types.h>
#include <rendering/TextureUVCoordinateSet.hpp>
#include <rendering/Textures.hpp>

struct DynamicTexture{
	TextureUVCoordinateSet uv;
UNK	int32_t field_18;
	uint8_t* data;
	int32_t dataLength;

	DynamicTexture(const TextureUVCoordinateSet&, int32_t);
	virtual ~DynamicTexture();
	virtual void tick(void) = 0;
	virtual void bindTexture(struct Textures*);
};
