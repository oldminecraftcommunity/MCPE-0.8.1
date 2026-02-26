#pragma once
#include <level/gen/feature/Feature.hpp>

struct ClayFeature : public Feature{
	int32_t id;
	int32_t size;
	ClayFeature();
	virtual ~ClayFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
