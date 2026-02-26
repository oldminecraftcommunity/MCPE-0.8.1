#pragma once
#include <_types.h>
#include <GL/gl.h>

struct DisableState{
	GLenum disabled;

	DisableState(GLenum s);
	~DisableState();
};
