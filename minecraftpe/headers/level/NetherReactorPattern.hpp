#pragma once
#include <_types.h>

struct NetherReactorPattern
{
	int32_t pattern[27];

	NetherReactorPattern();
	int32_t getTileAt(int32_t, int32_t, int32_t);
	void setTileAt(int32_t, int32_t, int32_t, int32_t);
};
