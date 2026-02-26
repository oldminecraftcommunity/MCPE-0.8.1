#pragma once
#include <_types.h>
#include <rendering/tileentity/TileEntityRenderer.hpp>
#include <rendering/model/ChestModel.hpp>

struct ChestRenderer: TileEntityRenderer
{
	ChestModel field_8, field_1A8;

	ChestRenderer();

	virtual ~ChestRenderer();
	virtual void render(struct TileEntity*, float, float, float, float, bool_t);
};
