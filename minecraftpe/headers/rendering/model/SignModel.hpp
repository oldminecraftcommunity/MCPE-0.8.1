#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct SignModel: Model
{
	ModelPart field_1C, field_9C;

	SignModel();

	virtual ~SignModel();
	virtual void render();
};
