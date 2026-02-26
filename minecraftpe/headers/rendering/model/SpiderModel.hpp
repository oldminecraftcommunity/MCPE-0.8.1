#pragma once
#include <rendering/model/Model.hpp>
#include <rendering/model/ModelPart.hpp>

struct SpiderModel: Model
{
	struct Eyes: Model
	{
		ModelPart field_1C;

		Eyes();

		virtual ~Eyes();
		virtual void render(Entity*, float, float, float, float, float, float);
		virtual void setupAnim(float, float, float, float, float, float);

	};

	ModelPart field_1C, field_9C, field_11C, field_19C;
	ModelPart field_21C, field_29C, field_31C, field_39C;
	ModelPart field_41C, field_49C, field_51C;

	SpiderModel();

	virtual ~SpiderModel();
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);


};
