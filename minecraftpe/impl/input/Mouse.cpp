#include <input/Mouse.hpp>

MouseDevice Mouse::_instance;

MouseAction::MouseAction(char a2, char a3, int16_t a4, int16_t a5, char a6){
	this->field_0 = a4;
	this->evButton = a2;
	this->state = a3;
	this->field_2 = a5;
	this->field_6 = 0;
	this->field_4 = 0;
	this->field_A = a6;
}

MouseAction::MouseAction(char a2, char a3, int16_t a4, int16_t a5, int16_t a6, int16_t a7, char a8){
	this->field_0 = a4;
	this->evButton = a2;
	this->state = a3;
	this->field_2 = a5;
	this->field_4 = a6;
	this->field_6 = a7;
	this->field_A = a8;
}

bool_t MouseAction::isButton() const{
	return (uint32_t)(uint8_t)this->evButton - 1 <= 1;
}

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

void MouseDevice::reset(){
	this->eventId = -1;
	this->mouseEvents.clear();
	this->field_13 = 0;
}
uint8_t MouseDevice::getButtonState(int32_t a2){
	if((uint32_t)(a2-1) > 2) return 0;
	return this->buttonStates[a2];
}

bool_t MouseDevice::isButtonDown(int32_t a2){
	return this->getButtonState(a2) != 0;
}
bool_t MouseDevice::wasFirstMovement(){
	return this->firstMovement == 1;
}
int16_t MouseDevice::getX(){
	return this->mouseX;
}

int16_t MouseDevice::getY(){
	return this->mouseY;
}
int16_t MouseDevice::getDX(){
	if(this->hasDX == -9999) return this->mouseX - this->prevMouseX;
	return this->hasDX;
}

int16_t MouseDevice::getDY(){
	if(this->hasDY == -9999) return this->mouseY - this->prevMouseY;
	return this->hasDY;
}

void MouseDevice::reset2(){
	this->prevMouseX = this->mouseX;
	this->prevMouseY = this->mouseY;
	this->hasDY = -9999;
	this->hasDX = -9999;
}
bool_t MouseDevice::next(){
	int32_t v1 = this->eventId+1;
	if(v1 >= this->mouseEvents.size()) return 0;
	this->eventId = v1;
	return 1;
}

void MouseDevice::rewind(void){
	this->eventId = -1;
}

bool_t MouseDevice::getEventButtonState(){
	return this->mouseEvents[this->eventId].state == 1;
}
int32_t MouseDevice::getEventButton(){
	return this->mouseEvents[this->eventId].evButton;
}

MouseAction* MouseDevice::getEvent(){
	return &this->mouseEvents[this->eventId];
}

void Mouse::reset(){
	return Mouse::_instance.reset();
}
int32_t Mouse::getButtonState(int32_t b){
	return Mouse::_instance.getButtonState(b);
}
bool_t Mouse::isButtonDown(int32_t b){
	return Mouse::_instance.isButtonDown(b);
}
int16_t Mouse::getX(){
	return Mouse::_instance.getX();
}
int16_t Mouse::getY(){
	return Mouse::_instance.getY();
}
int16_t Mouse::getDX(){
	return Mouse::_instance.getDX();
}
int16_t Mouse::getDY(){
	return Mouse::_instance.getDY();
}
void Mouse::reset2(){
	return Mouse::_instance.reset2();
}
bool_t Mouse::next(){
	return Mouse::_instance.next();
}
void Mouse::rewind(){
	return Mouse::_instance.rewind();
}
bool_t Mouse::getEventButtonState(){
	return Mouse::_instance.getEventButtonState();
}
int32_t Mouse::getEventButton(){
	return Mouse::_instance.getEventButton();
}
MouseAction* Mouse::getEvent(){
	return Mouse::_instance.getEvent();
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

void Mouse::feed(char a2, char a3, int16_t a4, int16_t a5, int16_t a6, int16_t a7){
	Mouse::_instance.feed(a2, a3, a4, a5, a6, a7);
}
void Mouse::feed(char a2, char a3, int16_t a4, int16_t a5){
	Mouse::feed(a2, a3, a4, a5, 0, 0);
}

void MouseDevice::feed(char a2, char a3, int16_t a4, int16_t a5){
	this->feed(a2, a3, a4, a5, 0, 0);
}
