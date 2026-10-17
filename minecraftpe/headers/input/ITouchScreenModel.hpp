#pragma once
#include <input/Mouse.hpp>

struct MouseAction;
struct ITouchScreenModel
{
	virtual ~ITouchScreenModel() {
	}
	virtual int32_t getPointerId(const MouseAction& a2) {
		return (uint8_t) (a2.field_A);
	}
	virtual int32_t getPointerId(int32_t a2, int32_t a3, int32_t a4) {
		return a4;
	}
};
