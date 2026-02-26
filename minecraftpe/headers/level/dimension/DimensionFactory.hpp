#pragma once
#include <_types.h>

struct DimensionFactory{
	static struct Dimension* createDefaultDimension(struct LevelData*);
};
