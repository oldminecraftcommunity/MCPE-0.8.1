#pragma once
#include <rendering/tileentity/TileEntityRenderer.hpp>
#include <rendering/model/ChestModel.hpp>

struct ChestRenderer: TileEntityRenderer
{
	ChestModel field_8, field_1A8;

	ChestRenderer() :
			TileEntityRenderer(), field_8(0), field_1A8(1) {
	}

	virtual ~ChestRenderer() {
	}
	virtual void render(struct TileEntity*, float, float, float, float, bool_t);
};
