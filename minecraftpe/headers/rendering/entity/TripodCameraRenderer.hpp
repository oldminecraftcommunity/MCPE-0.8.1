#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <rendering/TileRenderer.hpp>
#include <tile/Tile.hpp>
#include <rendering/model/ModelPart.hpp>

struct TripodCamera;
struct TripodCameraRenderer: EntityRenderer
{
	TileRenderer tileRenderer;
	Tile tile;
	ModelPart field_F0;

	TripodCameraRenderer();
	static float getFlashTime(const TripodCamera*, float);

	virtual ~TripodCameraRenderer();
	virtual void render(Entity*, float, float, float, float, float);

};
