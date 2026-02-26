#pragma once
#include <level/gen/feature/Feature.hpp>

struct SpruceFeature : public Feature{
	SpruceFeature(bool_t);

	virtual ~SpruceFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
