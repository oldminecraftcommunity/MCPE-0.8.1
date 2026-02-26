#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct QuadrupedModel: Model
{
	ModelPart field_18, field_98, field_118;
	ModelPart field_198, field_218, field_298, field_318;
	float field_398, field_39C;

	QuadrupedModel(int32_t, float, int32_t, int32_t);
	virtual ~QuadrupedModel();
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);
};
