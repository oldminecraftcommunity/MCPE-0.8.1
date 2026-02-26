#pragma once
#include <rendering/entity/MobRenderer.hpp>
#include <rendering/model/SpiderModel.hpp>

struct SpiderRenderer: MobRenderer
{
	SpiderModel::Eyes spiderEyes;
	SpiderRenderer(Model*, float);

	virtual ~SpiderRenderer();
	virtual int32_t prepareArmor(Mob*, int32_t, float);
	virtual float getFlipDegrees(Mob*);
	virtual void scale(Mob*, float);
};
