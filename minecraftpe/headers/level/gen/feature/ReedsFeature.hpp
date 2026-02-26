#pragma once
#include <level/gen/feature/Feature.hpp>

struct ReedsFeature : public Feature{
	ReedsFeature();

	virtual ~ReedsFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
