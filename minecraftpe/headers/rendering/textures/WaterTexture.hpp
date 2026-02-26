#pragma once
#include <rendering/textures/DynamicTexture.hpp>

struct WaterTexture: DynamicTexture
{
	int32_t field_28, field_2C;
	float *field_30, *field_34, *field_38, *field_3C;

	WaterTexture(const TextureUVCoordinateSet&);

	virtual ~WaterTexture();
	virtual void tick();
};
