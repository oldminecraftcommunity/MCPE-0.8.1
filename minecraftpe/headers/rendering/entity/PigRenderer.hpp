#pragma once
#include <rendering/entity/MobRenderer.hpp>

struct PigRenderer: MobRenderer
{
	PigRenderer(Model*, float);

	//TODO constructor

	virtual ~PigRenderer();
	virtual int32_t prepareArmor(Mob*, int32_t, float);
};
