#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <AppPlatform.hpp>
#include <rendering/MeshBuffer.hpp>

struct ArrowRenderer: EntityRenderer, AppPlatform::Listener
{
	MeshBuffer field_8;

	ArrowRenderer();

	virtual ~ArrowRenderer();
	virtual void render(Entity*, float, float, float, float, float);
	virtual void onAppSuspended();
};
