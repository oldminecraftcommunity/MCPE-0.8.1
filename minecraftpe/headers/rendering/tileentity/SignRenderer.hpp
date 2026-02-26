#pragma once
#include <rendering/tileentity/TileEntityRenderer.hpp>
#include <rendering/model/SignModel.hpp>

struct SignRenderer: TileEntityRenderer
{
	SignModel model;
	SignRenderer();

	virtual ~SignRenderer();
	virtual void render(TileEntity*, float, float, float, float, bool_t);
};
