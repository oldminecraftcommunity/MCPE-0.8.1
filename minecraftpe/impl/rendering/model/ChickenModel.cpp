#include <rendering/model/ChickenModel.hpp>
#include <math/Mth.hpp>

ChickenModel::ChickenModel()
	: field_18(0, 0, 64, 32)
	, field_98(0, 0, 64, 32)
	, field_118(0, 9, 64, 32)
	, field_198(26, 0, 64, 32)
	, field_218(26, 0, 64, 32)
	, field_298(24, 13, 64, 32)
	, field_318(24, 13, 64, 32)
	, field_398(14, 0, 64, 32)
	, field_418(14, 4, 64, 32) {
	this->field_18.setModel(this);
	this->field_398.setModel(this);
	this->field_418.setModel(this);
	this->field_118.setModel(this);
	this->field_198.setModel(this);
	this->field_218.setModel(this);
	this->field_298.setModel(this);
	this->field_318.setModel(this);
	this->field_18.addBox(-2.0, -6.0, -2.0, 4, 6, 3, 0.0);
	this->field_18.setPos(0.0, 15.0, -4.0);
	this->field_398.addBox(-2.0, -4.0, -4.0, 4, 2, 2, 0.0);
	this->field_398.setPos(0.0, 15.0, -4.0);
	this->field_418.addBox(-1.0, -2.0, -3.0, 2, 2, 2, 0.0);
	this->field_418.setPos(0.0, 15.0, -4.0);
	this->field_118.addBox(-3.0, -4.0, -3.0, 6, 8, 6, 0.0);
	this->field_118.setPos(0.0, 16.0, 0.0);
	this->field_198.addBox(-1.0, 0.0, -3.0, 3, 5, 3);
	this->field_198.setPos(-2.0, 19.0, 1.0);
	this->field_218.addBox(-1.0, 0.0, -3.0, 3, 5, 3);
	this->field_218.setPos(1.0, 19.0, 1.0);
	this->field_298.addBox(0.0, 0.0, -3.0, 1, 4, 6);
	this->field_298.setPos(-4.0, 13.0, 0.0);
	this->field_318.addBox(-1.0, 0.0, -3.0, 1, 4, 6);
	this->field_318.setPos(4.0, 13.0, 0.0);
	this->field_198.field_0 = 1;
	this->field_218.field_0 = 1;
}

ChickenModel::~ChickenModel() {
}
void ChickenModel::render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	this->setupAnim(a3, a4, a5, a6, a7, a8);
	glLightModelf(0xB52u, 1.0);
	if(this->field_14) {
		glPushMatrix();
		glTranslatef(0.0, a8 * 5.0, a8 + a8);
		this->field_18.render(a8);
		this->field_398.render(a8);
		this->field_418.render(a8);
		glPopMatrix();
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(0.0, a8 * 24.0, 0.0);
		this->field_118.render(a8);
		this->field_198.render(a8);
		this->field_218.render(a8);
		this->field_298.render(a8);
		this->field_318.render(a8);
		glPopMatrix();
	} else {
		this->field_18.render(a8);
		this->field_398.render(a8);
		this->field_418.render(a8);
		this->field_118.render(a8);
		this->field_198.render(a8);
		this->field_218.render(a8);
		this->field_298.render(a8);
		this->field_318.render(a8);
	}
	glLightModelf(0xB52u, 0.0);
}
void ChickenModel::setupAnim(float a2, float a3, float a4, float a5, float a6, float a7){
	float v7; // s14
	float v8; // s13
	float v9; // s15
	float v10; // s15

	v7 = a5 / (float)(180.0 / 3.1416);
	v8 = -(float)(a6 / (float)(180.0 / 3.1416));
	this->field_18.yRotAngle = v7;
	this->field_398.yRotAngle = v7;
	this->field_18.xRotAngle = v8;
	this->field_398.xRotAngle = v8;
	this->field_418.xRotAngle = v8;
	this->field_418.yRotAngle = v7;
	this->field_118.xRotAngle = 90.0 / (float)(180.0 / 3.1416);
	v9 = Mth::cos(a2 * 0.6662) * 1.4;
	this->field_298.zRotAngle = a4;
	v10 = v9 * a3;
	this->field_198.xRotAngle = v10;
	this->field_318.zRotAngle = -a4;
	this->field_218.xRotAngle = -v10;
}
