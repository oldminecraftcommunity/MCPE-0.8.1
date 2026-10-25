#pragma once
#include <_types.h>
#include <unigl.hpp>

struct EnableClientState{
	GLenum enabled;

	EnableClientState(){
		this->enabled = 0;
	}
	EnableClientState(GLenum s){
		this->enabled = s;
		if(this->enabled) glEnableClientState(this->enabled);
	}

	EnableClientState& operator=(EnableClientState&& s) {
		this->enabled = s.enabled;
		s.enabled = 0;
		return *this;
	}

	~EnableClientState() {
		if (this->enabled) {
			glDisableClientState(this->enabled);
		}
	}
};
