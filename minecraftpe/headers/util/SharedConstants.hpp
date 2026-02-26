#pragma once
#include <_types.h>

struct SharedConstants{
	static int32_t getVersionCode(int32_t a, int32_t b, int32_t c, int32_t d);
	static int32_t getVersionCode();
	static bool_t isVesion(int32_t a, int32_t b, int32_t c, int32_t d);
};
