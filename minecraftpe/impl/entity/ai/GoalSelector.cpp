#include <entity/ai/GoalSelector.hpp>
#include <algorithm>
#include <entity/ai/Goal.hpp>

GoalSelector::InternalGoal::InternalGoal(int32_t a2, struct Goal* a3, bool_t a4) {
	this->field_8 = a4;
	this->field_4 = a2;
	this->goal = a3;
	this->field_9 = 0;
}

void GoalSelector::addGoal(int32_t a2, struct Goal* a3, bool_t a4) {
	GoalSelector::InternalGoal* g = new GoalSelector::InternalGoal(a2, a3, a4);
	this->internalGoals.emplace_back(g);
}
bool_t GoalSelector::canCoExist(GoalSelector::InternalGoal* a2, GoalSelector::InternalGoal* a3) {
	int32_t cfags = a2->goal->getRequiredControlFlags();
	return (a2->goal->getRequiredControlFlags() & cfags) == 0;
}
bool_t GoalSelector::canUseInSystem(GoalSelector::InternalGoal* a2) {
	bool_t canCoExist;

	for(auto& g: this->internalGoals) {
		if(g != a2) {
			if(a2->field_4 < g->field_4) {
				if(g->field_9) {
					canCoExist = g->goal->canInterrupt();
					goto LABEL_6;
				}
			} else if(g->field_9) {
				canCoExist = this->canCoExist(a2, g);
LABEL_6:
				if(!canCoExist) {
					return 0;
				}
			}
		}
	}
	return 1;
}
std::vector<GoalSelector::InternalGoal*>* GoalSelector::getRunningGoals(void) {
	return &this->runningGoals;
}
void GoalSelector::tick() {
	this->field_18.clear();
	for(auto& g: this->internalGoals) {
		if(!g->field_9) {
			goto LABEL_8;
		}
		if(!this->canUseInSystem(g) || !g->goal->canContinueToUse()) {
			g->goal->stop();
			g->field_9 = 0;
			{
				auto&& el = std::find(this->runningGoals.begin(), this->runningGoals.end(), g);
				if(el != this->runningGoals.end()) {
					this->runningGoals.erase(el);
				}
			}
LABEL_8:
			if(this->canUseInSystem(g) && g->goal->canUse()) {
				g->field_9 = 1;
				this->field_18.push_back(g);
				this->runningGoals.push_back(g);
			}
		}
	}
	for(auto& g: this->field_18) {
		g->goal->start();
	}
	for(auto& g: this->runningGoals) {
		g->goal->tick();
	}
}
GoalSelector::~GoalSelector() {
	for(auto& goal: this->internalGoals) {
		if(goal->field_8) {
			if(goal->goal) delete goal->goal;
		}
		delete goal;
	}
}
