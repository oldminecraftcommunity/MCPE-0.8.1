#pragma once
#include <rendering/model/HumanoidModel.hpp>
#include <math/Mth.hpp>

struct ZombieModel: HumanoidModel
{
	ZombieModel()
		: HumanoidModel(0, 0) {
	}

	virtual ~ZombieModel() {
	}
	virtual void setupAnim(float a2, float a3, float a4, float a5, float a6, float a7) {

		HumanoidModel::setupAnim(a2, a3, a4, a5, a6, a7);
		if(!this->field_318 && !this->field_319) {
			float v9 = this->field_0;
			float v10 = Mth::sin(v9 * 3.1416f);
			float v11 = Mth::sin((1.0f - ((1.0f - v9) * (1.0f - v9))) * 3.1416f);
			float v12 = 0.1f - (v10 * 0.6f);
			this->rightArmModel.zRotAngle = 0.0f;
			this->leftArmModel.zRotAngle = 0.0f;
			this->leftArmModel.yRotAngle = v12;
			this->rightArmModel.yRotAngle = -v12;
			float v13 = - (float)(3.1416f * 0.5f) - (float)((float)(v10 * 1.2f) - (float)(v11 * 0.4f));
			this->rightArmModel.xRotAngle = v13;
			this->leftArmModel.xRotAngle = v13;
			float v14 = (float)(Mth::cos(a4 * 0.09f) * 0.05f) + 0.05f;
			float v15 = Mth::sin(a4 * 0.067f);
			this->rightArmModel.zRotAngle = v14 + 0.0f;
			this->leftArmModel.zRotAngle = 0.0f - v14;
			this->rightArmModel.xRotAngle = v13 + (float)(v15 * 0.05f);
			this->leftArmModel.xRotAngle = v13 - (float)(v15 * 0.05f);
		}
	}
};
