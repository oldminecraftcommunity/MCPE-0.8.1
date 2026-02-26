#include <rendering/model/SkeletonModel.hpp>
#include <entity/Mob.hpp>
#include <item/ItemInstance.hpp>

SkeletonModel::SkeletonModel() : ZombieModel(){
	this->rightArmModel = ModelPart(40, 16, 64, 32);
	this->rightArmModel.setModel(this);
	this->rightArmModel.addBox(-1.0, -2.0, -1.0, 2, 12, 2, 0.0);
	this->rightArmModel.setPos(-5.0, 2.0, 0.0);

	this->leftArmModel = ModelPart(40, 16, 64, 32);
	this->leftArmModel.setModel(this);
	this->leftArmModel.mirror = 1;
	this->leftArmModel.addBox(-1.0, -2.0, -1.0, 2, 12, 2, 0.0);
	this->leftArmModel.setPos(5.0, 2.0, 0.0);

	this->rightLegModel = ModelPart(0, 16, 64, 32);
	this->rightLegModel.setModel(this);
	this->rightLegModel.addBox(-1.0, 0.0, -1.0, 2, 12, 2, 0.0);
	this->rightLegModel.setPos(2.0, 12.0, 0.0);

	this->leftLegModel = ModelPart(0, 16, 64, 32);
	this->leftLegModel.setModel(this);
	this->leftLegModel.mirror = 1;
	this->leftLegModel.addBox(-1.0, 0.0, -1.0, 2, 12, 2, 0.0);
	this->leftLegModel.setPos(2.0, 12.0, 0.0);
	this->bodyModel.field_0 = 1;
}

SkeletonModel::~SkeletonModel() {
}
void SkeletonModel::render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	ItemInstance* item; // r7

	if(a2) {
		if(a2->isMob()) {
			item = ((Mob*)a2)->getCarriedItem();
			if(item) {
				if(((Mob*)a2)->getUseItemDuration() > 0 && item->getUseAnimation() == 4) {
					this->isUsingBow = 1;
				}
			}
		}
	}
	this->setupAnim(a3, a4, a5, a6, a7, a8);
	glLightModelf(0xB52u, 1.0);
	this->headModel.render(a8);
	this->bodyModel.render(a8);
	this->rightArmModel.render(a8);
	this->leftArmModel.render(a8);
	this->rightLegModel.render(a8);
	this->leftLegModel.render(a8);
	this->isUsingBow = 0;
	glLightModelf(0xB52u, 0.0);
}
void SkeletonModel::setupAnim(float a2, float a3, float a4, float a5, float a6, float a7) {
	this->isUsingBow = 1;
	ZombieModel::setupAnim(a2, a3, a4, a5, a6, a7);
}
