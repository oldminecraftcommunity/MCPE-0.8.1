#include <rendering/model/ChickenModel.hpp>
#include <math/Mth.hpp>

ChickenModel::ChickenModel()
	: headModel(0, 0, 64, 32)
	, field_98(0, 0, 64, 32)
	, bodyModel(0, 9, 64, 32)
	, leg1Model(26, 0, 64, 32)
	, leg2Model(26, 0, 64, 32)
	, wing1Model(24, 13, 64, 32)
	, wing2Model(24, 13, 64, 32)
	, beakModel(14, 0, 64, 32)
	, redThingModel(14, 4, 64, 32) {
	this->headModel.setModel(this);
	this->beakModel.setModel(this);
	this->redThingModel.setModel(this);
	this->bodyModel.setModel(this);
	this->leg1Model.setModel(this);
	this->leg2Model.setModel(this);
	this->wing1Model.setModel(this);
	this->wing2Model.setModel(this);
	this->headModel.addBox(-2.0, -6.0, -2.0, 4, 6, 3, 0.0);
	this->headModel.setPos(0.0, 15.0, -4.0);
	this->beakModel.addBox(-2.0, -4.0, -4.0, 4, 2, 2, 0.0);
	this->beakModel.setPos(0.0, 15.0, -4.0);
	this->redThingModel.addBox(-1.0, -2.0, -3.0, 2, 2, 2, 0.0);
	this->redThingModel.setPos(0.0, 15.0, -4.0);
	this->bodyModel.addBox(-3.0, -4.0, -3.0, 6, 8, 6, 0.0);
	this->bodyModel.setPos(0.0, 16.0, 0.0);
	this->leg1Model.addBox(-1.0, 0.0, -3.0, 3, 5, 3);
	this->leg1Model.setPos(-2.0, 19.0, 1.0);
	this->leg2Model.addBox(-1.0, 0.0, -3.0, 3, 5, 3);
	this->leg2Model.setPos(1.0, 19.0, 1.0);
	this->wing1Model.addBox(0.0, 0.0, -3.0, 1, 4, 6);
	this->wing1Model.setPos(-4.0, 13.0, 0.0);
	this->wing2Model.addBox(-1.0, 0.0, -3.0, 1, 4, 6);
	this->wing2Model.setPos(4.0, 13.0, 0.0);
	this->leg1Model.field_0 = 1;
	this->leg2Model.field_0 = 1;
}

void ChickenModel::render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	this->setupAnim(a3, a4, a5, a6, a7, a8);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
	if(this->field_14) {
		glPushMatrix();
		glTranslatef(0.0, a8 * 5.0, a8 + a8);
		this->headModel.render(a8);
		this->beakModel.render(a8);
		this->redThingModel.render(a8); //actual name from b1.2 btw (except ...Model thingy)
		glPopMatrix();
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(0.0, a8 * 24.0, 0.0);
		this->bodyModel.render(a8);
		this->leg1Model.render(a8);
		this->leg2Model.render(a8);
		this->wing1Model.render(a8);
		this->wing2Model.render(a8);
		glPopMatrix();
	} else {
		this->headModel.render(a8);
		this->beakModel.render(a8);
		this->redThingModel.render(a8);
		this->bodyModel.render(a8);
		this->leg1Model.render(a8);
		this->leg2Model.render(a8);
		this->wing1Model.render(a8);
		this->wing2Model.render(a8);
	}
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
}
void ChickenModel::setupAnim(float a2, float a3, float a4, float a5, float a6, float a7){

	float v7 = a5 / (180.0f / 3.1416f);
	float v8 = -(a6 / (180.0f / 3.1416f));
	this->headModel.yRotAngle = v7;
	this->beakModel.yRotAngle = v7;
	this->headModel.xRotAngle = v8;
	this->beakModel.xRotAngle = v8;
	this->redThingModel.xRotAngle = v8;
	this->redThingModel.yRotAngle = v7;
	this->bodyModel.xRotAngle = 90.0f / (180.0f / 3.1416f);
	float v9 = Mth::cos(a2 * 0.6662) * 1.4;
	this->wing1Model.zRotAngle = a4;
	float v10 = v9 * a3;
	this->leg1Model.xRotAngle = v10;
	this->wing2Model.zRotAngle = -a4;
	this->leg2Model.xRotAngle = -v10;
}
