#pragma once
#include <_types.h>

struct KeyboardAction
{
	int32_t field_0;
	uint8_t field_4;
	KeyboardAction(int a, uint8_t b)
		: field_0(a)
		, field_4(b) {
	}
	KeyboardAction(KeyboardAction&& act) = default;
};
