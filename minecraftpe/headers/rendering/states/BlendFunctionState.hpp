#pragma once
#include <_types.h>
#include <GL/gl.h>

struct BlendFunctionState{
	BlendFunctionState(GLenum sfactor, GLenum dfactor);
	~BlendFunctionState();
};
