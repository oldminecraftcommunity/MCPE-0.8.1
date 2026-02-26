#include <rendering/entity/SpiderRenderer.hpp>
#include <entity/Spider.hpp>

SpiderRenderer::SpiderRenderer(Model* a2, float a3)
	: MobRenderer(a2, a3), spiderEyes() {
	this->setArmor(&this->spiderEyes);
}

SpiderRenderer::~SpiderRenderer() {
}
int32_t SpiderRenderer::prepareArmor(Mob* a2, int32_t a3, float a4) {
	if(a3) return -1;
	this->bindTexture("mob/spider_eyes.png");
	glColor4f(1, 1, 1, 1);
	return 1;
}
float SpiderRenderer::getFlipDegrees(Mob*) {
	return 180;
}
void SpiderRenderer::scale(Mob* e, float a3) {
	float modelScale = ((Spider*)e)->getModelScale();
	glScalef(modelScale, modelScale, modelScale);
}
