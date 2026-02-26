#pragma once
#include <_types.h>
#include <AppPlatform.hpp>
#include <rendering/model/ModelPart.hpp>

struct Entity;
struct Mob;
struct Model: AppPlatform::Listener
{
	float field_0;
	int8_t field_4, field_5, field_6, field_7;
	std::vector<ModelPart*> parts;
	int32_t field_8, field_C, field_10;
	int8_t field_14, field_15, field_16, field_17;

	Model();
	virtual ~Model();
	virtual void onAppSuspended();
	virtual void clear();
	virtual void render();
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void renderHorrible(float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);
	virtual void prepareMobModel(Mob*, float, float, float);
};
