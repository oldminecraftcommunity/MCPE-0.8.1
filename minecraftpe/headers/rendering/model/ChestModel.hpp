#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct ChestModel: Model
{
	ModelPart field_18, field_98, field_118;
	bool_t field_198;
	int8_t field_199, field_19A, field_19B;

	ChestModel(bool_t);
	virtual ~ChestModel();
	virtual void render();
};
