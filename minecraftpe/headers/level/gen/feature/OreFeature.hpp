#pragma once
#include <level/gen/feature/Feature.hpp>

struct OreFeature : public Feature{
	int32_t id;
	int32_t amount;

	OreFeature(int32_t id, int32_t amount);
	virtual ~OreFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
