#pragma once
#include <_types.h>
#ifdef USEGLES
#include <unigl.hpp>
#endif
struct AppContext{
#ifdef USEGLES
	EGLDisplay  field_0;
	EGLContext field_4;
	EGLSurface field_8;
#else
	void* field_0;
	void* field_4;
	void* field_8;
#endif
	struct AppPlatform* platform;

	bool field_10;
};
