#include <entity/ai/goals/BreakDoorGoal.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <tile/DoorTile.hpp>

BreakDoorGoal::BreakDoorGoal(Mob* a2) : DoorInteractGoal(a2){

}

BreakDoorGoal::~BreakDoorGoal() {
}
bool_t BreakDoorGoal::canUse() {
	if(this->canUse()) {
		return !DoorTile::isOpen(this->holder->level, this->doorX, this->doorY, this->doorZ);
	}
	return 0;
}
bool_t BreakDoorGoal::canContinueToUse(){
	float v2; // s16

	v2 = this->holder->distanceToSqr((float)this->doorX, (float)this->doorY, (float)this->doorZ);
	return this->ticksLeft >= 0 && !DoorTile::isOpen(this->holder->level, this->doorX, this->doorY, this->doorZ) && v2 < 4.0;
}
void BreakDoorGoal::start() {
	DoorInteractGoal::start();
	this->ticksLeft = 240;
}
void BreakDoorGoal::tick() {
	int32_t v2;	  // r3
	Level* level; // r0

	this->tick();
	this->holder->level->random.genrand_int32();
	v2 = this->ticksLeft - 1;
	this->ticksLeft = v2;
	if(!v2) {
		level = this->holder->level;
		if(level->difficulty == 3) {
			level->setTile(this->doorX, this->doorY, this->doorZ, 0, 4);
			this->holder->level->levelEvent(2001, this->doorX, this->doorY, this->doorZ, this->doorTile->blockID);
		}
	}
}
