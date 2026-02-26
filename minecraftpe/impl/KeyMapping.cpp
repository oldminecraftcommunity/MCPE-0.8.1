#include <KeyMapping.hpp>

KeyMapping::KeyMapping(const std::string& name, int32_t code){
	this->name = name;
	this->keyCode = code;
}
KeyMapping::KeyMapping(){
	this->keyCode = 0;
}
void KeyMapping::operator=(KeyMapping&& key){
	this->keyCode = key.keyCode;
	this->name = key.name;
}
