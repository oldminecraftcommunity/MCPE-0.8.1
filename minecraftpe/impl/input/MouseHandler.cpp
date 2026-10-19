#include <input/MouseHandler.hpp>
#include <input/ITurnInput.hpp>

MouseHandler::MouseHandler(ITurnInput* turnInput){
	this->turnInput = turnInput;
}

MouseHandler::MouseHandler(){
	this->turnInput = 0;
}
MouseHandler::~MouseHandler(){
}
void MouseHandler::setTurnInput(ITurnInput* turnInp){
	this->turnInput = turnInp;
}

void MouseHandler::grab(){
	this->field_0 = 0;
	this->field_4 = 0;
}
void MouseHandler::release(){}

void MouseHandler::poll(){
	if(this->turnInput){
		Vec3 xy = this->turnInput->getTurnDelta();
		this->field_0 = xy.x;
		this->field_4 = xy.y;
	}
}

