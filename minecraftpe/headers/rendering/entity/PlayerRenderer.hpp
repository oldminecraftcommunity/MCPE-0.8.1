#pragma once
#include <rendering/entity/HumanoidMobRenderer.hpp>
#include <fh_frameanimod.hpp>

struct PlayerRenderer: HumanoidMobRenderer
{
	HumanoidModel* hmodel1;
	HumanoidModel* hmodel2;

	PlayerRenderer(HumanoidModel*, float);

	virtual ~PlayerRenderer();
	virtual void renderName(Entity*, float);
	void render(Entity* a2_, float a3, float a4, float a5, float a6, float a7) {
		animtime = a7;
		HumanoidMobRenderer::render(a2_, a3, a4, a5, a6, a7);
	}
	virtual int32_t prepareArmor(Mob*, int32_t, float);
	virtual void setupPosition(Entity*, float, float, float);
	virtual void setupRotations(Entity*, float, float, float);
	virtual int32_t getArmorTransparencyMode();
};
