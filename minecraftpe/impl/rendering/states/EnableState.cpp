#include <rendering/states/EnableState.hpp>

EnableState::EnableState(GLenum s){
	this->enabled = s;
	if(s) glEnable(this->enabled);
}

EnableState::~EnableState(){
	if(this->enabled) glDisable(this->enabled);
}
