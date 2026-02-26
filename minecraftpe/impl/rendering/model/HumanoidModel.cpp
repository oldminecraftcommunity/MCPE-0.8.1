#include <rendering/model/HumanoidModel.hpp>
#include <entity/Entity.hpp>
#include <entity/Mob.hpp>
#include <math/Mth.hpp>
#include <math.h>

HumanoidModel::HumanoidModel(float a2, float a3)
	: headModel(0, 0, 64, 32)
	, bodyModel(16, 16, 64, 32)
	, rightArmModel(40, 16, 64, 32)
	, leftArmModel(40, 16, 64, 32)
	, rightLegModel(0, 16, 64, 32)
	, leftLegModel(0, 16, 64, 32) {
	this->field_0 = 0;
	this->field_14 = 1;
	this->field_4 = 0;
	this->field_5 = 0;
	AppPlatform::_singleton->addListener(this, 1);
	this->field_318 = 0;
	this->field_319 = 0;
	this->field_31A = 0;
	this->isUsingBow = 0;
	this->headModel.setModel(this);
	this->bodyModel.setModel(this);
	this->rightArmModel.setModel(this);
	this->leftArmModel.setModel(this);
	this->rightLegModel.setModel(this);
	this->leftLegModel.setModel(this);
	this->headModel.addBox(-4.0, -8.0, -4.0, 8, 8, 8, a2);
	this->headModel.setPos(0.0, a3 + 0.0, 0.0);
	this->bodyModel.addBox(-4.0, 0.0, -2.0, 8, 12, 4, a2);
	this->bodyModel.setPos(0.0, a3 + 0.0, 0.0);
	this->rightArmModel.addBox(-3.0, -2.0, -2.0, 4, 12, 4, a2);
	this->rightArmModel.setPos(-5.0, a3 + 2.0, 0.0);
	this->leftArmModel.mirror = 1;
	this->leftArmModel.addBox(-1.0, -2.0, -2.0, 4, 12, 4, a2);
	this->leftArmModel.setPos(5.0, a3 + 2.0, 0.0);
	this->rightLegModel.addBox(-2.0, 0.0, -2.0, 4, 12, 4, a2);
	float v8 = a3 + 12.0;
	this->rightLegModel.setPos(-2.0, v8, 0.0);
	this->leftLegModel.mirror = 1;
	this->leftLegModel.addBox(-2.0, 0.0, -2.0, 4, 12, 4, a2);
	this->leftLegModel.setPos(2.0, v8, 0.0);
}

HumanoidModel::~HumanoidModel() {
}
void HumanoidModel::render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
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
	this->headModel.render(a8);
	this->bodyModel.render(a8);
	this->rightArmModel.render(a8);
	this->leftArmModel.render(a8);
	this->rightLegModel.render(a8);
	this->leftLegModel.render(a8);
	this->isUsingBow = 0;
}

void HumanoidModel::renderHorrible(float a2, float a3, float a4, float a5, float a6, float a7) {
	this->setupAnim(a2, a3, a4, a5, a6, a7);
	this->headModel.renderHorrible(a7);
	this->bodyModel.renderHorrible(a7);
	this->rightArmModel.renderHorrible(a7);
	this->leftArmModel.renderHorrible(a7);
	this->rightLegModel.renderHorrible(a7);
	this->leftLegModel.renderHorrible(a7);
}
void HumanoidModel::setupAnim(float a2, float a3, float a4, float a5, float a6, float a7) {
	float v10;		 // s19
	float v11;		 // s16
	float v12;		 // r0
	float v14;		 // s15
	float v15;		 // s15
	float v16;		 // s15
	float v17;		 // s16
	float v18;		 // r0
	float v19;		 // s21
	float v20;		 // s19
	float v21;		 // s22
	float v22;		 // r0
	float v23;		 // s15
	float v24;		 // s14
	float v25;		 // s16
	float v26;		 // r0
	float v28;		 // s15
	float yRotAngle; // s13
	float v30;		 // s14

	this->headModel.yRotAngle = a5 / (float)(180.0 / 3.1416);
	v10 = a2 * 0.6662;
	this->headModel.xRotAngle = a6 / (float)(180.0 / 3.1416);
	v11 = Mth::cos(a2 * 0.6662) * a3;
	v12 = Mth::cos(v10 + 3.1416);
	this->leftArmModel.xRotAngle = v11;
	this->rightArmModel.zRotAngle = 0.0;
	this->leftArmModel.zRotAngle = 0.0;
	this->rightLegModel.yRotAngle = 0.0;
	this->leftLegModel.yRotAngle = 0.0;
	this->rightArmModel.xRotAngle = v12 * a3;
	this->rightLegModel.xRotAngle = v11 * 1.4;
	this->leftLegModel.xRotAngle = (float)(v12 * a3) * 1.4;
	if(this->field_4) {
		v14 = -(float)(3.1416 * 0.5);
		this->rightArmModel.xRotAngle = (float)(v12 * a3) + (float)(v14 * 0.4);
		this->rightLegModel.xRotAngle = v14 * 0.8;
		this->leftLegModel.xRotAngle = v14 * 0.8;
		this->rightLegModel.yRotAngle = (float)(3.1416 * 0.5) * 0.2;
		this->leftLegModel.yRotAngle = v14 * 0.2;
		this->leftArmModel.xRotAngle = v11 + (float)(v14 * 0.4);
	}
	if(this->field_318) {
		this->leftArmModel.xRotAngle = (float)(this->leftArmModel.xRotAngle * 0.5) - (float)((float)(3.1416 * 0.5) * 0.2);
	}
	if(this->field_319) {
		this->rightArmModel.xRotAngle = (float)(this->rightArmModel.xRotAngle * 0.5) - (float)((float)(3.1416 * 0.5) * 0.2);
	}
	v15 = this->field_0;
	this->rightArmModel.yRotAngle = 0.0;
	this->leftArmModel.yRotAngle = 0.0;
	if(v15 > -9990.0) {
		v16 = sqrt(v15);
		v17 = Mth::sin((float)(v16 * 3.1416) + (float)(v16 * 3.1416)) * 0.2;
		this->bodyModel.yRotAngle = v17;
		this->rightArmModel.zOffset = Mth::sin(v17) * 5.0;
		this->rightArmModel.xOffset = -(float)(Mth::cos(v17) * 5.0);
		this->leftArmModel.zOffset = -(float)(Mth::sin(v17) * 5.0);
		v18 = Mth::cos(v17);
		v19 = this->field_0;
		this->leftArmModel.yRotAngle = this->leftArmModel.yRotAngle + v17;
		this->leftArmModel.xRotAngle = this->leftArmModel.xRotAngle + v17;
		this->leftArmModel.xOffset = v18 * 5.0;
		v20 = v17 + this->rightArmModel.yRotAngle;
		this->rightArmModel.yRotAngle = v20;
		v21 = Mth::sin((float)(1.0 - (float)((float)((float)(1.0 - v19) * (float)(1.0 - v19)) * (float)((float)(1.0 - v19) * (float)(1.0 - v19)))) * 3.1416);
		v22 = Mth::sin(v19 * 3.1416);
		v23 = this->headModel.xRotAngle - 0.7;
		this->rightArmModel.yRotAngle = v20 + (float)(v17 + v17);
		this->rightArmModel.xRotAngle = this->rightArmModel.xRotAngle - (float)((float)((float)-(float)(v23 * v22) * 0.75) + (float)(v21 * 1.2));
		this->rightArmModel.zRotAngle = Mth::sin(v19 * 3.1416) * -0.4;
	}
	if(this->field_31A) {
		v24 = this->rightArmModel.xRotAngle + 0.4;
		this->bodyModel.xRotAngle = 0.5;
		this->rightLegModel.zOffset = 4.0;
		this->leftLegModel.zOffset = 4.0;
		this->rightLegModel.yOffset = 9.0;
		this->leftLegModel.yOffset = 9.0;
		this->headModel.yOffset = 1.0;
		this->rightArmModel.xRotAngle = v24;
		this->leftArmModel.xRotAngle = this->leftArmModel.xRotAngle + 0.4;
	} else {
		this->bodyModel.xRotAngle = 0.0;
		this->rightLegModel.zOffset = 0.0;
		this->leftLegModel.zOffset = 0.0;
		this->headModel.yOffset = 0.0;
		this->rightLegModel.yOffset = 12.0;
		this->leftLegModel.yOffset = 12.0;
	}
	v25 = (float)(Mth::cos(a4 * 0.09) * 0.05) + 0.05;
	v26 = Mth::sin(a4 * 0.067);
	this->rightArmModel.zRotAngle = this->rightArmModel.zRotAngle + v25;
	v28 = v26 * 0.05;
	this->leftArmModel.zRotAngle = this->leftArmModel.zRotAngle - v25;
	this->rightArmModel.xRotAngle = this->rightArmModel.xRotAngle + (float)(v26 * 0.05);
	this->leftArmModel.xRotAngle = this->leftArmModel.xRotAngle - (float)(v26 * 0.05);
	if(this->isUsingBow) {
		yRotAngle = this->headModel.yRotAngle;
		this->rightArmModel.yRotAngle = yRotAngle - 0.1;
		this->leftArmModel.yRotAngle = (float)(yRotAngle + 0.1) + 0.4;
		v30 = this->headModel.xRotAngle - (float)(3.1416 * 0.5);
		this->rightArmModel.zRotAngle = v25 + 0.0;
		this->leftArmModel.zRotAngle = 0.0 - v25;
		this->rightArmModel.xRotAngle = v30 + v28;
		this->leftArmModel.xRotAngle = v30 - v28;
	}
}
