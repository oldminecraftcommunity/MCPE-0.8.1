#pragma once
#include <rendering/model/ZombieModel.hpp>

struct SkeletonModel: ZombieModel
{
	SkeletonModel();

	virtual ~SkeletonModel();
	virtual void render(Entity*, float, float, float, float, float, float);
	virtual void setupAnim(float, float, float, float, float, float);

};
