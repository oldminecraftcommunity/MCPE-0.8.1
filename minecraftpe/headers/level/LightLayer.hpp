#pragma once
#include <_types.h>

struct LightLayer
{
	static const LightLayer Block;
	static const LightLayer Sky;

	int32_t baseLight;
};
