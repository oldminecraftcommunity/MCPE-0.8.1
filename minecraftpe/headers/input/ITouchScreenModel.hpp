#pragma once
#include <_types.h>

struct MouseAction;
struct ITouchScreenModel
{
	virtual ~ITouchScreenModel();
	virtual int32_t getPointerId(const MouseAction&);
	virtual int32_t getPointerId(int32_t, int32_t, int32_t);
};
