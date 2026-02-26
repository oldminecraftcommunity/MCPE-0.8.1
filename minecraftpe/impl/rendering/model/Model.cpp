#include <rendering/model/Model.hpp>

Model::Model() {
	this->field_0 = 0;
	this->field_4 = 0;
	this->field_5 = 0;
	this->field_14 = 1;
	AppPlatform::_singleton->addListener(this, 1.0);
}
Model::~Model() {
	AppPlatform::_singleton->removeListener(this);
	for(auto& p: this->parts) {
		if(p) delete p;
	}
}
void Model::onAppSuspended() {
	this->clear();
}
void Model::clear() {
	for(auto& p: this->parts) {
		p->meshBuffer.reset();
	}
}
void Model::render() {
}
void Model::render(Entity*, float, float, float, float, float, float) {
	this->render();
}
void Model::renderHorrible(float, float, float, float, float, float) {
}
void Model::setupAnim(float, float, float, float, float, float) {
}
void Model::prepareMobModel(Mob*, float, float, float) {
}
