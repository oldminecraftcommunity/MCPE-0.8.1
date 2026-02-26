#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <AppPlatform.hpp>
#include <unordered_map>
#include <rendering/MeshBuffer.hpp>

struct Motive;
struct PaintingRenderer: EntityRenderer, AppPlatform::Listener
{
	std::unordered_map<const Motive*, MeshBuffer> motives;
	int32_t field_20, field_24;

	//TODO constructor
	MeshBuffer _buildPainting(int32_t, int32_t, int32_t, int32_t);
	MeshBuffer* _getMesh(const Motive*);

	virtual ~PaintingRenderer();
	virtual void render(Entity*, float, float, float, float, float);
	virtual void onAppSuspended();
};
