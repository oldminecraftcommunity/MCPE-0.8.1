#pragma once
#include <rendering/entity/MobRenderer.hpp>

struct SheepRenderer: MobRenderer
{
	Model* shearedModel;
	Model* furredModel;

	SheepRenderer(Model*, Model*, float);

	virtual ~SheepRenderer();
	virtual void render(Entity*, float, float, float, float, float);
	virtual int32_t prepareArmor(Mob*, int32_t, float);
};
