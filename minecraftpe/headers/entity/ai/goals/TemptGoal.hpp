#pragma once
#include <entity/ai/Goal.hpp>
#include <util/TempEPtr.hpp>
#include <vector>

struct Player;
struct PathfinderMob;
struct TemptGoal: Goal
{
	PathfinderMob* holder;
	float speedMultiplier;
	float field_10, field_14, field_18, field_1C, field_20;
	TempEPtr<Player> followedPlayer;
	int32_t timeout;
	bool_t running;
	int8_t field_3D, field_3E, field_3F;
	std::vector<int32_t> followItemIds;
	bool_t field_4C;
	bool_t prevAvoidWater;
	int8_t field_4E, field_4F;
	int32_t field_50;

	TemptGoal(PathfinderMob*, float, std::initializer_list<int32_t>, bool_t);
	bool_t isRunning();

	virtual ~TemptGoal();
	virtual bool_t canUse();
	virtual bool_t canContinueToUse();
	virtual void start();
	virtual void stop();
	virtual void tick();
};
