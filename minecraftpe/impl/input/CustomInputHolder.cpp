#include <input/CustomInputHolder.hpp>
#include <input/IMoveInput.hpp>
#include <input/IBuildInput.hpp>
#include <input/ITurnInput.hpp>
CustomInputHolder::CustomInputHolder(IMoveInput* move, ITurnInput* turn, IBuildInput* build) {
	this->mouseX = this->mouseY = 0;
	this->field_C = 0;
	this->moveInput = move;
	this->turnInput = turn;
	this->buildInput = build;
}

CustomInputHolder::~CustomInputHolder() {
	if(this->moveInput) delete this->moveInput;
	if(this->turnInput) delete this->turnInput;
	if(this->buildInput) delete this->buildInput;
}
IMoveInput* CustomInputHolder::getMoveInput() {
	return this->moveInput;
}
ITurnInput* CustomInputHolder::getTurnInput() {
	return this->turnInput;
}
IBuildInput* CustomInputHolder::getBuildInput() {
	return this->buildInput;
}
