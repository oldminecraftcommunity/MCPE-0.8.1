#pragma once
#include <level/gen/feature/Feature.hpp>

struct SpringFeature : public Feature{
	int32_t id;
	SpringFeature(int32_t id);

	virtual ~SpringFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
