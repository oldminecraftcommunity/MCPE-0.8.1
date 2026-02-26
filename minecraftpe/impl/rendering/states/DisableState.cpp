#include <rendering/states/DisableState.hpp>

DisableState::DisableState(GLenum s){
	this->disabled = s;
	if(s) glDisable(this->disabled);
}

DisableState::~DisableState(){
	if(this->disabled) glEnable(this->disabled);
}
