#pragma once
#include <_types.h>
#include <vector>

struct GoalSelector
{
	struct InternalGoal
	{
		struct Goal* goal;
		int32_t field_4;
		bool_t field_8;
		int8_t field_9, field_A, field_B;

		InternalGoal(int32_t, struct Goal*, bool_t);
	};

	std::vector<GoalSelector::InternalGoal*> internalGoals;
	std::vector<GoalSelector::InternalGoal*> runningGoals;
	std::vector<GoalSelector::InternalGoal*> field_18;

	void addGoal(int32_t a2, struct Goal* a3, bool_t a4);
	bool_t canCoExist(GoalSelector::InternalGoal*, GoalSelector::InternalGoal*);
	bool_t canUseInSystem(GoalSelector::InternalGoal*);
	std::vector<GoalSelector::InternalGoal*>* getRunningGoals(void);
	void tick();
	~GoalSelector();
};
