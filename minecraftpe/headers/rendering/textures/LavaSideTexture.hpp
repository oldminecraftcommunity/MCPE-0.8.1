#pragma once
#include <rendering/textures/DynamicTexture.hpp>

struct LavaSideTexture: DynamicTexture
{
	int32_t field_28, field_2C, field_30;
	float *field_34, *field_38, *field_3C, *field_40;

	LavaSideTexture(const TextureUVCoordinateSet&);

	virtual ~LavaSideTexture();
	virtual void tick();
};
