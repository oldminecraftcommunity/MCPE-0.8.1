#pragma once
#include <_types.h>
#include <GL/gl.h>

struct EnableState{
	GLenum enabled;

	EnableState(GLenum s);
	~EnableState();
};
