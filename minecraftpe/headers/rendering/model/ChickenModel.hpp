#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct ChickenModel: Model
{
	ModelPart headModel, field_98, bodyModel, leg1Model;
	ModelPart leg2Model, wing1Model, wing2Model, beakModel, redThingModel;

	ChickenModel();

	virtual ~ChickenModel() {
	}
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);
};
