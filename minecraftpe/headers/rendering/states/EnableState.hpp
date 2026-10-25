#pragma once
#include <_types.h>
#include <unigl.hpp>

struct EnableState{
	GLenum enabled;

	EnableState(GLenum s){
		this->enabled = s;
		if(s) glEnable(this->enabled);
	}
	EnableState& operator=(EnableState&& s) {
		this->enabled = s.enabled;
		s.enabled = 0;
		return *this;
	}
	~EnableState() {
		if (this->enabled) glDisable(this->enabled);
	}
};
