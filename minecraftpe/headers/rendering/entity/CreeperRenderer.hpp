#pragma once
#include <rendering/entity/MobRenderer.hpp>

struct CreeperRenderer: MobRenderer
{
	CreeperRenderer(Model*, float);

	virtual ~CreeperRenderer();
	virtual int32_t getOverlayColor(Mob*, float, float);
	virtual void scale(Mob*, float);
};
