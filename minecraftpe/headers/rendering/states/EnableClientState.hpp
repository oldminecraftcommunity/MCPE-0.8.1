#pragma once
#include <_types.h>
#include <GL/gl.h>

struct EnableClientState{
	GLenum enabled;

	EnableClientState();
	EnableClientState(GLenum s);
	~EnableClientState();
};
