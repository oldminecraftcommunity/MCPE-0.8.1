#include <rendering/model/CreeperModel.hpp>
#include <math/Mth.hpp>

CreeperModel::CreeperModel(float a2)
	: field_1C(0, 0, 64, 32)
	, field_9C(16, 16, 64, 32)
	, field_11C(0, 16, 64, 32)
	, field_19C(0, 16, 64, 32)
	, field_21C(0, 16, 64, 32)
	, field_29C(0, 16, 64, 32) {
	this->field_1C.setModel(this);
	this->field_9C.setModel(this);
	this->field_11C.setModel(this);
	this->field_19C.setModel(this);
	this->field_21C.setModel(this);
	this->field_29C.setModel(this);
	this->field_1C.addBox(-4.0, -8.0, -4.0, 8, 8, 8, a2);
	this->field_1C.setPos(0.0, 4.0, 0.0);
	this->field_9C.addBox(-4.0, 0.0, -2.0, 8, 12, 4, a2);
	this->field_9C.setPos(0.0, 4.0, 0.0);
	this->field_11C.addBox(-2.0, 0.0, -2.0, 4, 6, 4, a2);
	this->field_11C.setPos(-2.0, 16.0, 4.0);
	this->field_19C.addBox(-2.0, 0.0, -2.0, 4, 6, 4, a2);
	this->field_19C.setPos(2.0, 16.0, 4.0);
	this->field_21C.addBox(-2.0, 0.0, -2.0, 4, 6, 4, a2);
	this->field_21C.setPos(-2.0, 16.0, -4.0);
	this->field_29C.addBox(-2.0, 0.0, -2.0, 4, 6, 4, a2);
	this->field_29C.setPos(2.0, 16.0, -4.0);
}

CreeperModel::~CreeperModel() {
}
void CreeperModel::render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	this->setupAnim(a3, a4, a5, a6, a7, a8);
	this->field_1C.render(a8);
	this->field_9C.render(a8);
	this->field_11C.render(a8);
	this->field_19C.render(a8);
	this->field_21C.render(a8);
	this->field_29C.render(a8);
}
void CreeperModel::setupAnim(float a2, float a3, float a4, float a5, float a6, float a7){
	this->field_1C.yRotAngle = a5 / (float)(180.0 / 3.1416);
	this->field_1C.xRotAngle = a6 / (float)(180.0 / 3.1416);
	float v8 = (float)(Mth::cos(a2 * 0.6662) * 1.4) * a3;
	this->field_11C.xRotAngle = v8;
	this->field_29C.xRotAngle = v8;
	this->field_19C.xRotAngle = -v8;
	this->field_21C.xRotAngle = -v8;
}
