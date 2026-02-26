#include <entity/ai/goals/TemptGoal.hpp>
#include <entity/Player.hpp>
#include <entity/path/PathNavigation.hpp>
#include <entity/PathfinderMob.hpp>
#include <math.h>
#include <level/Level.hpp>
#include <entity/ai/LookControl.hpp>
#include <math/Mth.hpp>

TemptGoal::TemptGoal(PathfinderMob* a2, float a3, std::initializer_list<int32_t> a4, bool_t a6) {
	this->field_20 = 0.0;
	this->field_1C = 0.0;
	this->field_18 = 0.0;
	this->field_14 = 0.0;
	this->field_50 = 0;
	this->field_10 = 0.0;
	this->timeout = 0;
	this->running = 0;
	this->prevAvoidWater = 0;
	this->holder = a2;
	this->speedMultiplier = a3;
	this->followItemIds = a4;
	this->field_4C = a6;
	this->setRequiredControlFlags(3);
}
bool_t TemptGoal::isRunning() {
	return this->running;
}

TemptGoal::~TemptGoal() {
}
bool_t TemptGoal::canUse() {
	int32_t timeout; // r3
	Player* NearestPlayer; // r0
	Level* level; // r0
	ItemInstance* selectedItem; // r5

	timeout = this->timeout;
	if(timeout <= 0) {
		NearestPlayer = this->holder->level->getNearestPlayer(this->holder, 10.0);
		if(NearestPlayer != this->followedPlayer.entity) {
			if(NearestPlayer) {
				this->followedPlayer.entityId = NearestPlayer->entityId;
				level = NearestPlayer->level;
				this->followedPlayer.level = level;
				level->registerTemporaryPointer(&this->followedPlayer);
				this->followedPlayer.locked = 0;
			} else {
				this->followedPlayer.unset();
			}
		}
		if(this->followedPlayer.lock()) {
			selectedItem = this->followedPlayer.lock()->getSelectedItem();
			if(selectedItem) {
				for(int32_t& it: this->followItemIds) {
					if(selectedItem->getId() == it) {
						return 1;
					}
				}
			}
		}
	} else {
		this->timeout = timeout - 1;
	}
	return 0;
}
bool_t TemptGoal::canContinueToUse() {
	Entity* v2; // r5

	if(this->field_4C) {
		v2 = this->followedPlayer.lock();
		if(!v2) {
			return 0;
		}
		if(this->holder->distanceToSqr(v2) >= 36.0) {
			this->field_10 = v2->posX;
			this->field_14 = v2->posY;
			this->field_18 = v2->posZ;
		} else if(v2->distanceToSqr(this->field_10, this->field_14, this->field_18) > 0.16 || fabsf(v2->pitch - this->field_1C) > 5.0 || fabsf(v2->yaw - this->field_20) > 5.0) {
			return 0;
		}
		this->field_1C = v2->pitch;
		this->field_20 = v2->yaw;
	}
	return this->canUse();
}
void TemptGoal::start() {
	this->field_10 = this->followedPlayer.lock()->posX;
	this->field_14 = this->followedPlayer.lock()->posY;
	this->field_18 = this->followedPlayer.lock()->posZ;
	this->running = 1;
	this->prevAvoidWater = this->holder->getNavigation()->getAvoidWater();
	this->holder->getNavigation()->setAvoidWater(0);
}
void TemptGoal::stop() {
	if(this->followedPlayer.entity) {
		this->followedPlayer.unset();
	}
	this->holder->getNavigation()->stop();
	this->timeout = 100;
	this->running = 0;
	this->holder->getNavigation()->setAvoidWater(this->prevAvoidWater);
}
void TemptGoal::tick() {
	Entity* holder; // r7

	--this->field_50;
	this->holder->getLookControl()->setLookAt(this->followedPlayer.lock(), 30.0f, this->holder->getMaxHeadXRot());

	holder = (Entity*)this->holder;
	if(holder->distanceToSqr(this->followedPlayer.lock()) >= 6.25) {
		if(this->field_50 <= 0) {
			this->holder->getNavigation()->moveTo(this->followedPlayer.lock(), this->speedMultiplier);
			this->field_50 = Mth::fastRandom();
		}
	} else {
		this->holder->getNavigation()->stop();
	}
}
