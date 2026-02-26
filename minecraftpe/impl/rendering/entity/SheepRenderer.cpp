#include <rendering/entity/SheepRenderer.hpp>
#include <rendering/model/Model.hpp>
#include <entity/Sheep.hpp>

SheepRenderer::SheepRenderer(Model* a2, Model* a3, float a4)
	: MobRenderer(a2, a4) {
	this->shearedModel = a3;
	this->furredModel = a2;
}

SheepRenderer::~SheepRenderer() {
	this->model = 0;

	if(this->furredModel) delete this->furredModel;
	this->furredModel = 0;
	if(this->shearedModel) delete this->shearedModel;
	this->shearedModel = 0;
}
void SheepRenderer::render(Entity* a2, float a3, float a4, float a5, float a6, float a7) {
	if(((Sheep*)a2)->isSheared()) {
		this->model = this->shearedModel;
	} else {
		this->model = this->furredModel;
	}

	MobRenderer::render(a2, a3, a4, a5, a6, a7);
}
int32_t SheepRenderer::prepareArmor(Mob*, int32_t, float) {
	return -1;
}
