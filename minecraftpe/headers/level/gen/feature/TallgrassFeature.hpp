#pragma once
#include <level/gen/feature/Feature.hpp>

struct TallgrassFeature: public Feature
{
	int32_t blockID;
	int32_t field_C;

	TallgrassFeature(int32_t blockID, int32_t c);

	virtual ~TallgrassFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
