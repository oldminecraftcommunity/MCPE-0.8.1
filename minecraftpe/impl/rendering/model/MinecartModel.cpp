#include <rendering/model/MinecartModel.hpp>

MinecartModel::MinecartModel()
	: Model() {
	this->field_18[0] = ModelPart(0, 10, 64, 32);
	this->field_18[1] = ModelPart(0, 0, 64, 32);
	this->field_18[2] = ModelPart(0, 0, 64, 32);
	this->field_18[3] = ModelPart(0, 0, 64, 32);
	this->field_18[4] = ModelPart(0, 0, 64, 32);
	this->field_18[5] = ModelPart(44, 10, 64, 32);

	this->field_18[0].addBox(-10.0, -8.0, -1.0, 20, 16, 2, 0.0);
	this->field_18[0].setPos(0.0, 4.0, 0.0);
	this->field_18[5].addBox(-9.0, -7.0, -1.0, 18, 14, 1, 0.0);
	this->field_18[5].setPos(0.0, 4.0, 0.0);
	this->field_18[1].addBox(-8.0, -9.0, -1.0, 16, 8, 2, 0.0);
	this->field_18[1].setPos(-9.0, 4.0, 0.0);
	this->field_18[2].addBox(-8.0, -9.0, -1.0, 16, 8, 2, 0.0);
	this->field_18[2].setPos(9.0, 4.0, 0.0);
	this->field_18[3].addBox(-8.0, -9.0, -1.0, 16, 8, 2, 0.0);
	this->field_18[3].setPos(0.0, 4.0, -7.0);
	this->field_18[4].addBox(-8.0, -9.0, -1.0, 16, 8, 2, 0.0);
	this->field_18[4].setPos(0.0, 4.0, 7.0);
	this->field_18[0].xRotAngle = 3.1416 * 0.5;
	this->field_18[2].yRotAngle = 3.1416 * 0.5;
	this->field_18[1].yRotAngle = (float)(3.1416 * 0.5) * 3.0;
	this->field_18[5].xRotAngle = -(float)(3.1416 * 0.5);
	this->field_18[3].yRotAngle = (float)(3.1416 * 0.5) + (float)(3.1416 * 0.5);
}
MinecartModel::~MinecartModel() {
}
void MinecartModel::render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	this->field_18[5].yOffset = 4 - a5;
	for(int32_t i = 0; i != 6; ++i) {
		this->field_18[i].render(a8);
	}
}
