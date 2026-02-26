#pragma once
#include <_types.h>

struct FrustumData{

	float planes[16][16];
	float proj[16];
	float modl[16];
	float clip[16];

	bool_t cubeInFrustum(float, float, float, float, float, float);
};
