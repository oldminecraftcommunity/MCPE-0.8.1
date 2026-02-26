#pragma once
#include <rendering/entity/EntityRenderer.hpp>

struct TileRenderer;
struct FallingTileRenderer: EntityRenderer
{
	TileRenderer* tileRenderer;

	FallingTileRenderer();

	virtual ~FallingTileRenderer();
	virtual void render(Entity*, float, float, float, float, float);
};
