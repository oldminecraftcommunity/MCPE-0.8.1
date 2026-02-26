#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct HumanoidModel: Model
{
	ModelPart headModel, bodyModel;
	ModelPart rightArmModel, leftArmModel;
	ModelPart rightLegModel, leftLegModel;
	int8_t field_318, field_319, field_31A;
	bool_t isUsingBow;
	int32_t field_31C;

	HumanoidModel(float, float);

	virtual ~HumanoidModel();
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void renderHorrible(float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);
};
