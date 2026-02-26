#pragma once
#include <_types.h>

struct TickNextTickData{

	static int32_t C;

	int32_t id;
	int32_t x, y, z;
	int32_t field_10;
	int32_t delay;

	TickNextTickData(int32_t, int32_t, int32_t, int32_t);
	int32_t hashCode(void);
	bool_t operator<(const TickNextTickData&) const;
	bool_t operator==(const TickNextTickData&) const;
	void setDelay(int32_t);
};
