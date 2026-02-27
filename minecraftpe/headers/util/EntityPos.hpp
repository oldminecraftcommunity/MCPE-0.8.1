#pragma once
#include <_types.h>

struct EntityPos
{
	float x, y, z;
	float yaw, pitch;
	bool_t hasRot, hasXYZ;
	char field_16, field_17;
};
