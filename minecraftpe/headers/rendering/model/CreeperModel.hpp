#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct CreeperModel: Model
{
	ModelPart field_1C, field_9C, field_11C, field_19C, field_21C, field_29C;

	CreeperModel(float);

	virtual ~CreeperModel();
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);

};
