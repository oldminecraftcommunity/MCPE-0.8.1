#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct HumanoidModel: Model
{
	ModelPart headModel, bodyModel;
	ModelPart rightArmModel, leftArmModel;
	ModelPart rightLegModel, leftLegModel;
	bool field_318, carryingItem, sneaking, isUsingBow;

	HumanoidModel(float, float);

	virtual ~HumanoidModel(){}
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void renderHorrible(float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);
};
