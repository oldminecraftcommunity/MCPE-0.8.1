#include <rendering/model/SignModel.hpp>

SignModel::SignModel()
	: field_1C(0, 0, 64, 32)
	, field_9C(0, 14, 64, 32) {
	this->field_1C.addBox(-12.0, -14.0, -1.0, 24, 12, 2, 0.0);
	this->field_9C.addBox(-1.0, -2.0, -1.0, 2, 14, 2, 0.0);
	this->field_1C.setModel(this);
	this->field_9C.setModel(this);
}

SignModel::~SignModel() {
}
void SignModel::render(){
	this->field_1C.render(0.060606);
	this->field_9C.render(0.0625);
}
