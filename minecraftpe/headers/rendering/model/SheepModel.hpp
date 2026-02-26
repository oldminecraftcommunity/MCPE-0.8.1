#pragma once
#include <rendering/model/QuadrupedModel.hpp>

struct SheepModel: QuadrupedModel
{
	float headEatAngleScale;

	SheepModel(bool_t);

	virtual ~SheepModel();
	virtual void setupAnim(float, float, float, float, float, float);
	virtual void prepareMobModel(Mob*, float, float, float);
};
