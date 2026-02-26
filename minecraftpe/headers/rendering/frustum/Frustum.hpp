#pragma once
#include <_types.h>
#include <rendering/frustum/FrustumData.hpp>

struct Frustum: FrustumData
{
	static Frustum frustum;

	void calculateFrustum(void);
	void normalizePlane(float (*)[16], int32_t);
};
