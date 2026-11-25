#pragma once
#include <rendering/entity/MobRenderer.hpp>
#include <rendering/model/SpiderModel.hpp>
#include <entity/Spider.hpp>

struct SpiderRenderer: MobRenderer
{
	SpiderModel::Eyes spiderEyes;
	SpiderRenderer(float a3) :
			MobRenderer(new SpiderModel(), a3), spiderEyes() {
		this->setArmor(&this->spiderEyes);
	}

	virtual ~SpiderRenderer() {
	}
	virtual int32_t prepareArmor(Mob* a2, int32_t a3, float a4) {
		if (a3) return -1;

		this->bindTexture("mob/spider_eyes.png");
		glColor4f(1, 1, 1, 1);
		return 1;
	}
	virtual float getFlipDegrees(Mob*) {
		return 180;
	}
	virtual void scale(Mob* e, float a3) {
		float modelScale = ((Spider*) (e))->getModelScale();
		glScalef(modelScale, modelScale, modelScale);
	}
};
