#pragma once
#include <_types.h>

struct _TickPtr
{
	virtual void invalidate() = 0;
	virtual ~_TickPtr();
};
