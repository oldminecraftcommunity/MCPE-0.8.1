#include <input/MouseDevice.hpp>

MouseDevice::MouseDevice(){
	this->hasDX = -9999;
	this->eventId = -1;
	this->hasDY = -9999;
	this->mouseX = 0;
	this->mouseY = 0;
	this->prevMouseX = 0;
	this->prevMouseY = 0;
	this->firstMovement = 0;
	this->buttonStates[0] = 0;
	this->buttonStates[1] = 0;
	this->field_12 = 0;
	this->field_13 = 0;
}

void MouseDevice::feed(char a2, char a3, int16_t a4, int16_t a5){
	this->feed(a2, a3, a4, a5, 0, 0);
}

void MouseDevice::feed(char a2, char a3, int16_t mx, int16_t my, int16_t a6, int16_t a7){
	int32_t v9 = a2;

	this->mouseEvents.push_back(MouseAction(a2, a3, mx, my, a6, a7, 0));
	if(v9 == 0){
		if(this->hasDX == -9999) this->hasDX = 0;
		if(this->hasDY == -9999) this->hasDY = 0;
		this->hasDX = a6+this->hasDX;
		this->hasDY = a7+this->hasDY;
		this->firstMovement = this->firstMovement == -1;
	}else{
		this->buttonStates[v9] = a3;
		if(v9 == 1){
			this->firstMovement = -1;
		}
	}



	this->prevMouseX = this->mouseX;
	this->mouseX = mx;

	this->prevMouseY = this->mouseY;
	this->mouseY = my;
}

uint8_t MouseDevice::getButtonState(int32_t a2){
	if((uint32_t)(a2-1) > 2) return 0;
	return this->buttonStates[a2];
}
int16_t MouseDevice::getDX(){
	if(this->hasDX == -9999) return this->mouseX - this->prevMouseX;
	return this->hasDX;
}

int16_t MouseDevice::getDY(){
	if(this->hasDY == -9999) return this->mouseY - this->prevMouseY;
	return this->hasDY;
}

MouseAction* MouseDevice::getEvent(){
	return &this->mouseEvents[this->eventId];
}

int32_t MouseDevice::getEventButton(){
	return this->mouseEvents[this->eventId].evButton;
}

bool_t MouseDevice::getEventButtonState(){
	return this->mouseEvents[this->eventId].state == 1;
}

int16_t MouseDevice::getX(){
	return this->mouseX;
}

int16_t MouseDevice::getY(){
	return this->mouseY;
}

bool_t MouseDevice::isButtonDown(int32_t a2){
	return this->getButtonState(a2) != 0;
}

bool_t MouseDevice::next(){
	int32_t v1 = this->eventId+1;
	if(v1 >= this->mouseEvents.size()) return 0;
	this->eventId = v1;
	return 1;
}

void MouseDevice::reset(){
	this->eventId = -1;
	this->mouseEvents.clear();
	this->field_13 = 0;
}

void MouseDevice::reset2(){
	this->prevMouseX = this->mouseX;
	this->prevMouseY = this->mouseY;
	this->hasDY = -9999;
	this->hasDX = -9999;
}

void MouseDevice::rewind(void){
	this->eventId = -1;
}

bool_t MouseDevice::wasFirstMovement(){
	return this->firstMovement == 1;
}
