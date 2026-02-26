#pragma once
#include <rendering/model/HumanoidModel.hpp>

struct ZombieModel: HumanoidModel
{
	ZombieModel();

	virtual ~ZombieModel();
	virtual void setupAnim(float, float, float, float, float, float);

};
