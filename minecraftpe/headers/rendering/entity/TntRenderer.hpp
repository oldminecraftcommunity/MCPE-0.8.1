#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <rendering/TileRenderer.hpp>

struct TntRenderer: EntityRenderer
{
	TileRenderer tileRenderer;

	TntRenderer();

	virtual ~TntRenderer();
	virtual void render(Entity*, float, float, float, float, float);
};
