#pragma once
#include <AppContext.hpp>

struct ENGINE{
#ifdef ANDROID
	struct android_app* state;
#else
	void* state;
#endif

	int32_t field_4;
#ifdef USEGLES
	EGLDisplay field_8;
	EGLSurface surface;
	EGLContext field_10;
#else
	void* field_8;
	void* surface;
	void* field_10;
#endif
	int32_t width, height;
	int32_t field_1C;
	struct Minecraft* minecraft;
	int8_t field_24;
	AppContext appCtx;
};
