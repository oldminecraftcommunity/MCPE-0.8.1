#pragma once
#include <rendering/entity/MobRenderer.hpp>

struct HumanoidModel;
struct HumanoidMobRenderer: MobRenderer
{
	HumanoidModel* hmodel;

	HumanoidMobRenderer(HumanoidModel*, float);
	void renderHand();

	virtual ~HumanoidMobRenderer();
	virtual void render(Entity*, float, float, float, float, float);
	virtual void additionalRendering(Mob*, float);
};
