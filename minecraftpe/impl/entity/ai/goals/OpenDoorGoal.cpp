#include <entity/ai/goals/OpenDoorGoal.hpp>
#include <tile/DoorTile.hpp>
#include <entity/Mob.hpp>

OpenDoorGoal::OpenDoorGoal(Mob* a2, bool_t a3)
	: DoorInteractGoal(a2) {
	this->holder = a2;
	this->field_28 = a3;
}

OpenDoorGoal::~OpenDoorGoal() {
}
bool_t OpenDoorGoal::canContinueToUse() {
	return this->field_28 && this->ticksLeft > 0 && this->canContinueToUse();
}
void OpenDoorGoal::start(){
	this->ticksLeft = 20;
	((DoorTile*)this->doorTile)->setOpen(this->holder->level, this->doorX, this->doorY, this->doorZ, 1);
}
void OpenDoorGoal::stop() {
	if(this->field_28) {
		((DoorTile*)this->doorTile)->setOpen(this->holder->level, this->doorX, this->doorY, this->doorZ, 0);
	}
}
void OpenDoorGoal::tick() {
	--this->ticksLeft;
	DoorInteractGoal::tick();
}
