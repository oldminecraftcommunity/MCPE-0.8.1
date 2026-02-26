#pragma once
#include <rendering/entity/MobRenderer.hpp>

struct ChickenRenderer: MobRenderer
{
	ChickenRenderer(Model*, float);

	virtual ~ChickenRenderer();
	virtual float getBob(Mob*, float);
};
