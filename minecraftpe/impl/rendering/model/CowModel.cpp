#include <rendering/model/CowModel.hpp>

CowModel::CowModel()
	: QuadrupedModel(12, 0, 64, 32) {
	this->field_18 = ModelPart(0, 0, 64, 32);
	this->field_18.setModel(this);
	this->field_18.addBox(-4.0, -4.0, -6.0, 8, 8, 6, 0.0);
	this->field_18.setPos(0.0, 4.0, -8.0);
	this->field_18.texOffs(22, 0)->addBox(-5.0, -5.0, -4.0, 1, 3, 1, 0.0);
	this->field_18.texOffs(22, 0)->addBox(4.0, -5.0, -4.0, 1, 3, 1, 0.0);

	this->field_118 = ModelPart(18, 4, 64, 32);
	this->field_118.setModel(this);
	this->field_118.addBox(-6.0, -10.0, -7.0, 12, 18, 10, 0.0);
	this->field_118.setPos(0.0, 5.0, 2.0);
	this->field_118.texOffs(52, 0)->addBox(-2.0, 2.0, -8.0, 4, 6, 1);
	this->field_198.xOffset = this->field_198.xOffset - 1.0;
	this->field_218.xOffset = this->field_218.xOffset + 1.0;
	this->field_198.zOffset = this->field_198.zOffset + 0.0;
	float v5 = this->field_298.xOffset - 1.0;
	this->field_218.zOffset = this->field_218.zOffset + 0.0;
	this->field_298.xOffset = v5;
	this->field_318.xOffset = this->field_318.xOffset + 1.0;
	this->field_298.zOffset = this->field_298.zOffset - 1.0;
	this->field_318.zOffset = this->field_318.zOffset - 1.0;
	this->field_39C = this->field_39C + 2.0;
}

CowModel::~CowModel() {
}
