#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <rendering/TileRenderer.hpp>
#include <rendering/model/MinecartModel.hpp>

struct MinecartRenderer: EntityRenderer
{
	TileRenderer tileRenderer;
	MinecartModel mmodel;

	MinecartRenderer();
	void renderMinecartContents(Entity*, float, Tile*, int32_t);

	virtual ~MinecartRenderer();
	virtual void render(Entity*, float, float, float, float, float);
};
