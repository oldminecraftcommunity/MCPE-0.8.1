#pragma once
#include <level/gen/feature/Feature.hpp>

struct BirchFeature : public Feature{
	BirchFeature(bool_t);

	virtual ~BirchFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
