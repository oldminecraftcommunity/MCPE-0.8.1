#pragma once
#include <entity/ai/goals/TargetGoal.hpp>
#include <level/Level.hpp>

struct Player;
struct NearestAttackableTargetGoal: TargetGoal
{
	Player* targetedPlayer;
	int32_t field_18, field_1C;
	NearestAttackableTargetGoal(Mob* mob, float radius) :
			TargetGoal(mob, radius, 1) {
		this->field_18 = 1;
		this->field_1C = 0;
		this->setRequiredControlFlags(1);
	}

	virtual ~NearestAttackableTargetGoal() {
	}
	virtual bool_t canUse() {
		if (this->field_1C > 0 && this->mob->random.nextInt(this->field_1C)) {
			return 0;
		}

		Player* nearestPlayer;
		if (this->field_18 == 1) {
			nearestPlayer = this->mob->level->getNearestPlayer(this->mob, this->radius);
		} else {
			nearestPlayer = 0;
		}
		if (this->canAttack(nearestPlayer, 0)) {
			this->targetedPlayer = nearestPlayer;
			return 1;
		}
		return 0;
	}
	virtual void start() {
		this->mob->setTarget(this->targetedPlayer);
	}
};
