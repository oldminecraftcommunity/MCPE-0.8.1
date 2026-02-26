#pragma once
#include <_types.h>

struct Entity;
struct DistanceEntitySorter
{
	float x, y, z;
	bool_t operator()(const Entity*, const Entity*);
};
