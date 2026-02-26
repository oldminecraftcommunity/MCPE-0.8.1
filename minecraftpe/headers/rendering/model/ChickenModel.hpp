#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct ChickenModel: Model
{
	ModelPart field_18, field_98, field_118, field_198;
	ModelPart field_218, field_298, field_318, field_398, field_418;

	ChickenModel();

	virtual ~ChickenModel();
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);
};
