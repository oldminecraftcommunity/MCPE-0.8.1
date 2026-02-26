#pragma once
#include <_types.h>

struct Vec3;
struct PathfinderMob;
struct RandomPos
{
	static bool_t generateRandomPos(Vec3& res, PathfinderMob*, int32_t, int32_t, Vec3*);
};
