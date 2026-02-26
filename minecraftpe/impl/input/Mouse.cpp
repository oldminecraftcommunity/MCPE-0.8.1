#include <input/Mouse.hpp>

MouseDevice Mouse::_instance;

void Mouse::feed(int8_t a2, int8_t a3, int16_t a4, int16_t a5){
	Mouse::feed(a2, a3, a4, a5, 0, 0);
}
void Mouse::feed(int8_t a2, int8_t a3, int16_t a4, int16_t a5, int16_t a6, int16_t a7){
	Mouse::_instance.feed(a2, a3, a4, a5, a6, a7);
}
int32_t Mouse::getButtonState(int32_t b){
	return Mouse::_instance.getButtonState(b);
}
int16_t Mouse::getDX(){
	return Mouse::_instance.getDX();
}
int16_t Mouse::getDY(){
	return Mouse::_instance.getDY();
}
MouseAction* Mouse::getEvent(){
	return Mouse::_instance.getEvent();
}
int32_t Mouse::getEventButton(){
	return Mouse::_instance.getEventButton();
}
bool_t Mouse::getEventButtonState(){
	return Mouse::_instance.getEventButtonState();
}
int16_t Mouse::getX(){
	return Mouse::_instance.getX();
}
int16_t Mouse::getY(){
	return Mouse::_instance.getY();
}
bool_t Mouse::isButtonDown(int32_t b){
	return Mouse::_instance.isButtonDown(b);
}
bool_t Mouse::next(){
	return Mouse::_instance.next();
}
void Mouse::reset(){
	return Mouse::_instance.reset();
}
void Mouse::reset2(){
	return Mouse::_instance.reset2();
}
void Mouse::rewind(){
	return Mouse::_instance.rewind();
}
