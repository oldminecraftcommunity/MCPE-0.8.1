#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <AppPlatform.hpp>
#include <rendering/MeshBuffer.hpp>

struct Item;
struct ItemSpriteRenderer: EntityRenderer, AppPlatform::Listener
{
	MeshBuffer meshBuffer;
	std::string textureFile;
	Item* item;

	ItemSpriteRenderer(Item*);

	virtual ~ItemSpriteRenderer();
	virtual void render(Entity*, float, float, float, float, float);
	virtual void onAppSuspended();
};
