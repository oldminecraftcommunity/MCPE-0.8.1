#pragma once
#include <util/IPosTranslator.hpp>

struct OffsetPosTranslator: IPosTranslator
{
	float x, y, z;
	OffsetPosTranslator();

	virtual ~OffsetPosTranslator();
	virtual void to(int32_t&, int32_t&, int32_t&);
	virtual void to(float&, float&, float&);
	virtual void from(int32_t&, int32_t&, int32_t&);
	virtual void from(float&, float&, float&);
};
