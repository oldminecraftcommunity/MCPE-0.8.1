#pragma once
#include <_types.h>

struct TileEntityFactory
{
	static struct TileEntity* createTileEntity(int32_t type);
};
