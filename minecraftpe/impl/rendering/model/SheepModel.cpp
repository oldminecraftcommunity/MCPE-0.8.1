#include <rendering/model/SheepModel.hpp>
#include <entity/Sheep.hpp>

SheepModel::SheepModel(bool_t a2)
	: QuadrupedModel(12, 0, 64, 64) {
	if(a2) {
		this->field_118 = ModelPart(28, 8, 64, 64);
		this->field_118.addBox(-4.0, -10.0, -7.0, 8, 16, 6, 0.0);
	} else {
		this->field_118 = ModelPart(this, 28, 40, 64, 64);
		this->field_118.addBox(-4.0, -10.0, -7.0, 8, 16, 6, 1.75);
	}
	this->field_118.setPos(0.0, 5.0, 2.0);
	this->field_18 = ModelPart(this, 0, 0, 64, 64);
	this->field_18.addBox(-3.0, -4.0, -6.0, 6, 6, 8, 0.0);
	this->field_18.setPos(0.0, 6.0, -8.0);
	if(!a2) {
		this->field_18.texOffs(0, 32)->addBox(-3.0, -4.0, -4.0, 6, 6, 6, 0.6);
		this->field_198.texOffs(0, 48)->addBox(-2.0, 0.0, -2.0, 4, 6, 4, 0.5);
		this->field_218.texOffs(0, 48)->addBox(-2.0, 0.0, -2.0, 4, 6, 4, 0.5);
		this->field_298.texOffs(0, 48)->addBox(-2.0, 0.0, -2.0, 4, 6, 4, 0.5);
		this->field_318.texOffs(0, 48)->addBox(-2.0, 0.0, -2.0, 4, 6, 4, 0.5);
	}
}

SheepModel::~SheepModel() {
}
void SheepModel::setupAnim(float a2, float a3, float a4, float a5, float a6, float a7) {
	QuadrupedModel::setupAnim(a2, a3, a4, a5, a6, a7);
	this->field_18.xRotAngle = this->headEatAngleScale;
}
void SheepModel::prepareMobModel(Mob* a2, float a3, float a4, float a5) {
	this->field_18.yOffset = (((Sheep*)a2)->getHeadEatPositionScale(a5) * 9.0) + 6.0;
	this->headEatAngleScale = ((Sheep*)a2)->getHeadEatAngleScale(a5);
}
