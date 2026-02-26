#include <rendering/states/EnableClientState.hpp>

EnableClientState::EnableClientState(){
	this->enabled = 0;
}
EnableClientState::EnableClientState(GLenum s){
	this->enabled = s;
	if(this->enabled) glEnableClientState(this->enabled);
}

EnableClientState::~EnableClientState(){
	if(this->enabled){
		glDisableClientState(this->enabled);
	}

}
