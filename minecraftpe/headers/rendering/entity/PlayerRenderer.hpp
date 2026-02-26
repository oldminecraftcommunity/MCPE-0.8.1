#pragma once
#include <rendering/entity/HumanoidMobRenderer.hpp>

struct PlayerRenderer: HumanoidMobRenderer
{
	HumanoidModel* hmodel1;
	HumanoidModel* hmodel2;

	PlayerRenderer(HumanoidModel*, float);

	virtual ~PlayerRenderer();
	virtual void renderName(Entity*, float);
	virtual int32_t prepareArmor(Mob*, int32_t, float);
	virtual void setupPosition(Entity*, float, float, float);
	virtual void setupRotations(Entity*, float, float, float);
	virtual int32_t getArmorTransparencyMode();
};
