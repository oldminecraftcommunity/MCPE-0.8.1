#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <AppPlatform.hpp>
#include <unordered_map>
#include <rendering/MeshBuffer.hpp>

struct Motive;
struct PaintingRenderer: EntityRenderer, AppPlatform::Listener
{
	std::unordered_map<const Motive*, MeshBuffer> motives;

	PaintingRenderer()
		: EntityRenderer() {
		AppPlatform::_singleton->addListener(this, 1.0f);
	}

	MeshBuffer _buildPainting(int32_t, int32_t, int32_t, int32_t);
	MeshBuffer* _getMesh(const Motive*);

	virtual ~PaintingRenderer() {
		AppPlatform::_singleton->removeListener(this);
	}
	virtual void render(Entity*, float, float, float, float, float);
	virtual void onAppSuspended() {
		this->motives.clear();
	}
};
