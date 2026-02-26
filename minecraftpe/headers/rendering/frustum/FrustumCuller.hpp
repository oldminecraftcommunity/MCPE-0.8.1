#pragma once
#include <_types.h>
#include <rendering/frustum/FrustumData.hpp>

struct FrustumCuller{
	FrustumData data;
	float xOff, yOff, zOff;

	bool_t isVisible(const struct AABB&);
};
