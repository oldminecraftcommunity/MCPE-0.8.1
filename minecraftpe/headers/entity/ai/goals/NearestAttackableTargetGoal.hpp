#pragma once
#include <entity/ai/goals/TargetGoal.hpp>

struct Player;
struct NearestAttackableTargetGoal: TargetGoal
{
	Player* targetedPlayer;
	int32_t field_18, field_1C;
	NearestAttackableTargetGoal(Mob*, float radius);

	virtual ~NearestAttackableTargetGoal();
	virtual bool_t canUse();
	virtual void start();
};
