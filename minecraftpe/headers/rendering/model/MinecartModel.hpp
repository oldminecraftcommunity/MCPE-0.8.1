#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct MinecartModel: Model
{
	ModelPart field_18[7];

	MinecartModel();
	virtual ~MinecartModel();
	virtual void render(Entity*, float, float, float, float, float, float);

};
