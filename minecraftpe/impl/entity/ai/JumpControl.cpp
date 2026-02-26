#include <entity/ai/JumpControl.hpp>
#include <entity/Mob.hpp>

JumpControl::JumpControl(Mob* a2) {
	this->controlledEntity = a2;
	this->isJumping = 0;
}
void JumpControl::jump() {
	this->isJumping = 1;
}

void JumpControl::tick() {
	this->controlledEntity->setJumping(this->isJumping);
	this->isJumping = 0;
}
JumpControl::~JumpControl(){

}
