#include <rendering/model/PigModel.hpp>

PigModel::PigModel(float a2)
	: QuadrupedModel(6, a2, 64, 32) {
	this->field_18.texOffs(16, 16)->addBox(-2.0, 0.0, -9.0, 4, 3, 1, a2);
	this->field_398 = 4;
}

PigModel::~PigModel() {
}
