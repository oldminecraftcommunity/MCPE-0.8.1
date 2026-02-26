#pragma once
#include <level/gen/feature/Feature.hpp>

struct FlowerFeature : public Feature{
	int32_t id;

	FlowerFeature(int32_t id);

	virtual ~FlowerFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
