#pragma once
#include <level/gen/feature/Feature.hpp>

struct TreeFeature : public Feature{
	int32_t meta;
	TreeFeature(bool_t, int32_t meta);

	virtual ~TreeFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
