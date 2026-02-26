#include <rendering/model/SpiderModel.hpp>
#include <math.h>
#include <math/Mth.hpp>

SpiderModel::Eyes::Eyes()
	: field_1C(32, 4, 64, 32) {
	this->field_5 = 1;
	this->field_1C.setModel(this);
	this->field_1C.addBox(-4.0, -4.0, -8.0, 8, 8, 8, 0.0);
	this->field_1C.setPos(0, 15, -3);
}
SpiderModel::Eyes::~Eyes() {
}
void SpiderModel::Eyes::render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8){
	this->setupAnim(a3, a4, a5, a6, a7, a8);
	glEnable(0x8037u);
	this->field_1C.render(a8);
	glDisable(0x8037u);
}
void SpiderModel::Eyes::setupAnim(float a2, float a3, float a4, float a5, float a6, float a7) {
	this->field_1C.yRotAngle = a5 / (float)(180 / 3.1416);
	this->field_1C.xRotAngle = a6 / (float)(180 / 3.1416);
}

SpiderModel::SpiderModel() : field_1C(32, 4, 64, 32), field_9C(0, 0, 64, 32), field_11C(0, 12, 64, 32), field_19C(18, 0, 64, 32), field_21C(18, 0, 64, 32), field_29C(18, 0, 64, 32), field_31C(18, 0, 64, 32), field_39C(18, 0, 64, 32), field_41C(18, 0, 64, 32), field_49C(18, 0, 64, 32), field_51C(18, 0, 64, 32){
	this->field_1C.setModel(this);
	this->field_9C.setModel(this);
	this->field_11C.setModel(this);
	this->field_19C.setModel(this);
	this->field_21C.setModel(this);
	this->field_29C.setModel(this);
	this->field_31C.setModel(this);
	this->field_39C.setModel(this);
	this->field_41C.setModel(this);
	this->field_49C.setModel(this);
	this->field_51C.setModel(this);
	this->field_1C.addBox(-4.0, -4.0, -8.0, 8, 8, 8, 0.0);
	this->field_1C.setPos(0.0, 15.0, -3.0);
	this->field_9C.addBox(-3.0, -3.0, -3.0, 6, 6, 6, 0.0);
	this->field_9C.setPos(0.0, 15.0, 0.0);
	this->field_11C.addBox(-5.0, -4.0, -6.0, 10, 8, 12, 0.0);
	this->field_11C.setPos(0.0, 15.0, 9.0);
	this->field_19C.addBox(-15.0, -1.0, -1.0, 16, 2, 2, 0.0);
	this->field_19C.setPos(-4.0, 15.0, 2.0);
	this->field_21C.addBox(-1.0, -1.0, -1.0, 16, 2, 2, 0.0);
	this->field_21C.setPos(4.0, 15.0, 2.0);
	this->field_29C.addBox(-15.0, -1.0, -1.0, 16, 2, 2, 0.0);
	this->field_29C.setPos(-4.0, 15.0, 1.0);
	this->field_31C.addBox(-1.0, -1.0, -1.0, 16, 2, 2, 0.0);
	this->field_31C.setPos(4.0, 15.0, 1.0);
	this->field_39C.addBox(-15.0, -1.0, -1.0, 16, 2, 2, 0.0);
	this->field_39C.setPos(-4.0, 15.0, 0.0);
	this->field_41C.addBox(-1.0, -1.0, -1.0, 16, 2, 2, 0.0);
	this->field_41C.setPos(4.0, 15.0, 0.0);
	this->field_49C.addBox(-15.0, -1.0, -1.0, 16, 2, 2, 0.0);
	this->field_49C.setPos(-4.0, 15.0, -1.0);
	this->field_51C.addBox(-1.0, -1.0, -1.0, 16, 2, 2, 0.0);
	this->field_51C.setPos(4.0, 15.0, -1.0);
}

SpiderModel::~SpiderModel() {
}
void SpiderModel::render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	this->setupAnim(a3, a4, a5, a6, a7, a8);
	this->field_1C.render(a8);
	this->field_9C.render(a8);
	this->field_11C.render(a8);
	this->field_19C.render(a8);
	this->field_21C.render(a8);
	this->field_29C.render(a8);
	this->field_31C.render(a8);
	this->field_39C.render(a8);
	this->field_41C.render(a8);
	this->field_49C.render(a8);
	this->field_51C.render(a8);
}
void SpiderModel::setupAnim(float a2, float a3, float a4, float a5, float a6, float a7) {
	float* v13; // r9
	float* v14; // r8
	float v15;	// s21
	float v16;	// s31
	float v17;	// s20
	float v18;	// s24
	float v19;	// s27
	float v20;	// s30
	float v21;	// s28
	float v22;	// s28
	float v23;	// s22
	float v24;	// s23
	float v25;	// s26
	float v26;	// s30
	float v27;	// s29
	float v28;	// r0
	float v29;	// s29
	float v30;	// s17
	float v31;	// [sp+0h] [bp-68h]
	float v32;	// [sp+4h] [bp-64h]
	v13 = &this->field_49C.yRotAngle;
	v14 = &this->field_51C.yRotAngle;
	this->field_1C.yRotAngle = a5 / (float)(180.0 / 3.1416);
	this->field_1C.xRotAngle = a6 / (float)(180.0 / 3.1416);
	this->field_21C.zRotAngle = 3.1416 * 0.25;
	v15 = a2 * 0.6662;
	v16 = (float)((float)(3.1416 + 3.1416) * 0.0) * 0.25;
	v17 = -(float)(3.1416 * 0.25);
	this->field_19C.zRotAngle = v17;
	v18 = (float)(3.1416 * 0.25) * 0.74;
	this->field_29C.zRotAngle = v17 * 0.74;
	this->field_39C.zRotAngle = v17 * 0.74;
	this->field_31C.zRotAngle = v18;
	this->field_41C.zRotAngle = v18;
	this->field_49C.zRotAngle = v17;
	this->field_51C.zRotAngle = 3.1416 * 0.25;
	this->field_21C.yRotAngle = v17;
	this->field_29C.yRotAngle = 3.1416 * 0.125;
	this->field_19C.yRotAngle = 3.1416 * 0.25;
	v19 = -(float)(3.1416 * 0.125);
	this->field_31C.yRotAngle = v19;
	this->field_39C.yRotAngle = v19;
	this->field_41C.yRotAngle = 3.1416 * 0.125;
	this->field_49C.yRotAngle = v17;
	this->field_51C.yRotAngle = 3.1416 * 0.25;
	v20 = (float)((float)(3.1416 + 3.1416) + (float)(3.1416 + 3.1416)) * 0.25;
	v21 = -(float)(0.4 * Mth::cos((float)(v15 + v15) + v16));
	v31 = (float) - (float)(0.4 * Mth::cos((float)(v15 + v15) + v20)) * a3;
	v22 = v21 * a3;
	v32 = (float) - (float)(0.4 * Mth::cos((float)(v15 + v15) + (float)((float)(3.1416 + 3.1416) * 0.25))) * a3;
	v23 = (float)((float)(3.1416 + 3.1416) * 3.0) * 0.25;
	v24 = (float) - (float)(0.4 * Mth::cos((float)(v15 + v15) + v23)) * a3;
	v25 = fabsf(Mth::sin(v15 + v16) * 0.4) * a3;
	v26 = fabsf(Mth::sin(v15 + v20) * 0.4) * a3;
	v27 = Mth::sin(v15 + (float)((float)(3.1416 + 3.1416) * 0.25)) * 0.4;
	v28 = Mth::sin(v15 + v23);
	this->field_21C.yRotAngle = v17 - v22;
	this->field_31C.yRotAngle = v19 - v31;
	v29 = fabsf(v27) * a3;
	this->field_19C.yRotAngle = (float)(3.1416 * 0.25) + v22;
	this->field_29C.yRotAngle = (float)(3.1416 * 0.125) + v31;
	this->field_39C.yRotAngle = v32 - (float)(3.1416 * 0.125);
	this->field_41C.yRotAngle = (float)(3.1416 * 0.125) - v32;
	*v13 = v24 - (float)(3.1416 * 0.25);
	*v14 = (float)(3.1416 * 0.25) - v24;
	this->field_19C.zRotAngle = v25 - (float)(3.1416 * 0.25);
	v30 = fabsf(v28 * 0.4) * a3;
	this->field_29C.zRotAngle = (float)(v17 * 0.74) + v26;
	this->field_21C.zRotAngle = (float)(3.1416 * 0.25) - v25;
	this->field_31C.zRotAngle = v18 - v26;
	this->field_39C.zRotAngle = (float)(v17 * 0.74) + v29;
	this->field_41C.zRotAngle = v18 - v29;
	this->field_49C.zRotAngle = v30 - (float)(3.1416 * 0.25);
	this->field_51C.zRotAngle = (float)(3.1416 * 0.25) - v30;
}
