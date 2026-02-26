#include <rendering/entity/PigRenderer.hpp>
#include <entity/Pig.hpp>
#include <rendering/model/PigModel.hpp>

PigRenderer::PigRenderer(Model* a2, float a3)
	: MobRenderer(a2, a3) {
	this->setArmor(new PigModel(0.5));
}

PigRenderer::~PigRenderer() {
	Model* armouwur = this->getArmor();
	if(armouwur) delete armouwur;
}
int32_t PigRenderer::prepareArmor(Mob* a2, int32_t a3, float a4) {
	if(!((Pig*)a2)->hasSaddle() || a3 > 0) return -1;
	this->bindTexture("mob/saddle.png");
	return 1;
}
