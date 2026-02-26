#include <entity/ai/goals/EatTileGoal.hpp>
#include <math/Mth.hpp>
#include <tile/Tile.hpp>
#include <level/Level.hpp>
#include <entity/Mob.hpp>
#include <entity/path/PathNavigation.hpp>

EatTileGoal::EatTileGoal(Mob* a2) {
	this->holder = a2;
	this->ticksLeft = 0;
	this->level = a2->level;
	this->setRequiredControlFlags(7);
}

EatTileGoal::~EatTileGoal() {
}
bool_t EatTileGoal::canUse() {
	Mob* holder; // r0
	Random* p_random; // r7
	uint32_t v4; // r6
	Mob* v5; // r8
	int32_t v6; // r7
	int32_t v7; // r6
	int32_t v8; // r8
	int32_t result; // r0

	holder = this->holder;
	p_random = &holder->level->random;
	if(holder->isBaby()) {
		v4 = 50;
	} else {
		v4 = 1000;
	}
	if(p_random->genrand_int32() % v4) {
		return 0;
	}
	v5 = this->holder;
	v6 = Mth::floor(v5->posX);
	v7 = Mth::floor(v5->posY);
	v8 = Mth::floor(v5->posZ);
	if(this->level->getTile(v6, v7, v8) != Tile::tallgrass->blockID) {
		return this->level->getTile(v6, v7 - 1, v8) == Tile::grass->blockID;
	}
	result = this->level->getData(v6, v7, v8);
	if(result != 1) {
		return this->level->getTile(v6, v7 - 1, v8) == Tile::grass->blockID;
	}
	return result;
}
bool_t EatTileGoal::canContinueToUse() {
	return this->ticksLeft > 0;
}
void EatTileGoal::start() {
	this->ticksLeft = 40;
	this->level->broadcastEntityEvent(this->holder, 10);
	this->holder->getNavigation()->stop();
}
void EatTileGoal::stop() {
	this->ticksLeft = 0;
}
void EatTileGoal::tick() {
	int v2; // r5
	Mob* holder; // r6
	int v4; // r7
	int v5; // r8
	int v6; // r6
	int v7; // r0

	v2 = (this->ticksLeft - 1) & ~((this->ticksLeft - 1) >> 31);
	this->ticksLeft = v2;
	if(v2 == 4) {
		holder = this->holder;
		v4 = Mth::floor(holder->posX);
		v5 = Mth::floor(holder->posY) - 1;
		v6 = Mth::floor(holder->posZ);
		v7 = this->level->getTile(v4, v5, v6);
		if(v7 == Tile::grass->blockID) {
			this->level->levelEvent(2001, v4, v5, v6, v7);
			this->level->setTile(v4, v5, v6, Tile::dirt->blockID, 4);
			this->holder->ate();
		}
	}
}
int32_t EatTileGoal::getEatAnimationTick() {
	return this->ticksLeft;
}
void EatTileGoal::setLevel(Level* level) {
	this->level = level;
}
