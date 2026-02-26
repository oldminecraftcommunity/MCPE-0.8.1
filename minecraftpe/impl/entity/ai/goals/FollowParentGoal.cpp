#include <entity/ai/goals/FollowParentGoal.hpp>
#include <entity/Animal.hpp>
#include <entity/path/PathNavigation.hpp>
#include <float.h>
#include <level/Level.hpp>

FollowParentGoal::FollowParentGoal(Animal* a2, float a3)
	: Goal() {
	this->holder = a2;
	this->speedMultiplier = a3;
	this->ticksFollowing = 0;
}
FollowParentGoal::~FollowParentGoal() {
}
bool_t FollowParentGoal::canUse() {
	Entity* v2;		// r5
	Animal* holder; // r0
	float v4;		// s16
	Level* level;	// r6
	int32_t v6;		// r0
	Animal* v7;		// r3
	float maxY;		// s13
	float maxX;		// s12
	float minX;		// s9
	float v11;		// s10
	float v12;		// s14
	float maxZ;		// s13
	float v17;		// r0
	Level* v18;		// r0

	v2 = 0;
	if(this->holder->getAge() < 0) {
		holder = this->holder;
		v4 = FLT_MAX;
		std::vector<Entity*> v20;
		level = holder->level;
		v6 = holder->getEntityTypeId();
		v7 = this->holder;
		maxY = v7->boundingBox.maxY;
		maxX = v7->boundingBox.maxX;
		minX = v7->boundingBox.minX;
		v11 = v7->boundingBox.minY - 4.0;

		AABB v21{minX - 8.0f, v11, v7->boundingBox.minZ - 8.0f, maxX + 8.0f, maxY + 4.0f, v7->boundingBox.maxZ + 8.0f};
		level->getEntitiesOfType(v6, v21, v20);
		for(auto& v16: v20) {
			if(((Animal*)v16)->getAge() >= 0) {
				v17 = this->holder->distanceToSqr(v16);
				if(v17 <= v4) {
					v4 = v17;
					v2 = v16;
				}
			}
		}

		if(v2) {
			if(v4 < 9.0) {
				return 0;
			} else {
				if(v2 != this->parent.entity) {
					this->parent.entityId = v2->entityId;
					v18 = v2->level;
					this->parent.level = v18;
					v18->registerTemporaryPointer(&this->parent);
					this->parent.locked = 0;
				}
				return 1;
			}
		}
	}
	return 0;
}
bool_t FollowParentGoal::canContinueToUse() {
	Mob* v3;		// r0
	Entity* holder; // r5
	Entity* v6;		// r0
	float v7;		// r0

	if(this->parent.lock() && (v3 = this->parent.lock(), v3->isAlive()) && (holder = (Entity*)this->holder, v6 = this->parent.lock(), v7 = holder->distanceToSqr(v6), v7 >= 9.0)) {
		return v7 <= 256.0;
	} else {
		return 0;
	}
}
void FollowParentGoal::start() {
	this->ticksFollowing = 0;
}
void FollowParentGoal::stop() {
	if(this->parent.entity) {
		this->parent.unset();
	}
}
void FollowParentGoal::tick() {
	if(this->ticksFollowing - 1 <= 0) {
		this->ticksFollowing = 10;
		this->holder->getNavigation()->moveTo(this->parent.lock(), this->speedMultiplier);
	} else {
		--this->ticksFollowing;
	}
}
