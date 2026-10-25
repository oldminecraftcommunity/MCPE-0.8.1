#pragma once
#include <_types.h>
#include <unigl.hpp>

struct DisableState{
	GLenum disabled;

	DisableState(GLenum s){
		this->disabled = s;
		if(s) glDisable(this->disabled);
	}
	DisableState& operator=(DisableState&& s) {
		this->disabled = s.disabled;
		s.disabled = 0;
		return *this;
	}
	~DisableState() {
		if (this->disabled) glEnable(this->disabled);
	}
};
