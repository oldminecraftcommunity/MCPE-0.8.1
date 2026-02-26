#include <rendering/model/ChestModel.hpp>

ChestModel::ChestModel(bool_t a2)
	: field_18(0, 0, 64, 32)
	, field_98(0, 0, 64, 32)
	, field_118(0, 0, 64, 32) {
	float v4 = -8.0;
	int32_t v5;	 // r9
	int32_t v6;	 // r3
	float v8;	 // s17
	int32_t v11; // [sp+14h] [bp-BCh]

	if(a2) {
		v5 = 128;
	} else {
		v5 = 64;
	}
	if(a2) {
		v6 = 30;
	} else {
		v6 = 14;
	}
	this->field_198 = a2;
	v11 = v6;
	if(!a2) {
		v4 = 0.0;
	}
	this->field_18 = *ModelPart(this, 0, 0, 64, 32).setTexSize(v5, 64);
	this->field_18.addBox(0.0, -5.0, -14.0, v11, 5, 14, 0.0);
	v8 = v4 + 1.0;
	this->field_18.yOffset = 7.0;
	this->field_18.zOffset = 15.0;
	this->field_18.xOffset = v8;
	this->field_118 = *ModelPart(this, 0, 0, 64, 32).setTexSize(v5, 64);
	this->field_118.addBox(-1.0, -2.0, -15.0, 2, 4, 1, 0.0);
	this->field_118.yOffset = 7.0;
	this->field_118.xOffset = 8.0;
	this->field_118.zOffset = 15.0;
	this->field_98 = *ModelPart(this, 0, 19, 64, 32).setTexSize(v5, 64);
	this->field_98.addBox(0.0, 0.0, 0.0, v11, 10, 14, 0.0);
	this->field_98.xOffset = v8;
	this->field_98.zOffset = 1.0;
	this->field_98.yOffset = 6.0;
}
ChestModel::~ChestModel() {
}
void ChestModel::render() {
	this->field_118.xRotAngle = this->field_18.xRotAngle;
	this->field_18.render(0.0625);
	this->field_118.render(0.0625);
	this->field_98.render(0.0625);
}
