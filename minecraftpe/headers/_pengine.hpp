#pragma once
#include <_types.h>
#include <AppContext.hpp>

struct _PEngine{
	int32_t field_0, field_4, field_8;
	struct AppPlatform* platform;
	int32_t field_10;
	int32_t width, height;
	int32_t field_1C;
	struct Minecraft* minecraft;
	int8_t field_24;
	AppContext appCtx;
};
