#pragma once
#include <_types.h>

struct IPosTranslator
{
	virtual ~IPosTranslator();
	virtual void to(int32_t&, int32_t&, int32_t&) = 0;
	virtual void to(float&, float&, float&) = 0;
	virtual void from(int32_t&, int32_t&, int32_t&) = 0;
	virtual void from(float&, float&, float&) = 0;
};
