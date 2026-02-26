#pragma once
#include <AppPlatform.hpp>
#include <_types.h>
#include <item/ItemInstance.hpp>
#include <memory>
#include <rendering/RenderCall.hpp>
#include <rendering/TextureUVCoordinateSet.hpp>
#include <rendering/TileRenderer.hpp>
#include <unordered_map>

struct ItemInHandRenderer: AppPlatform::Listener
{
	ItemInstance field_4;
	struct Minecraft* minecraft;
	float field_1C;
	float field_20;
	TileRenderer tileRenderer;
	std::unordered_map<int32_t, std::unique_ptr<RenderCall>> field_90;

	ItemInHandRenderer(struct Minecraft*);
	int32_t _getFrameID(struct Mob*, ItemInstance*);
	void itemPlaced();
	void itemUsed();

	RenderCall* rebuildItem(struct Mob*, ItemInstance&);
	void render(float);
	void renderFire(float);
	void renderItem(struct Mob*, ItemInstance*);
	void renderScreenEffect(float);
	void renderTex(float, const TextureUVCoordinateSet&);
	void renderWater(float);
	void tick();

	virtual ~ItemInHandRenderer();
	virtual void onAppSuspended();
};
