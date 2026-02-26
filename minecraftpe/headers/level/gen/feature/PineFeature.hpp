#pragma once
#include <level/gen/feature/Feature.hpp>

struct PineFeature : public Feature{
	PineFeature();
	virtual ~PineFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
