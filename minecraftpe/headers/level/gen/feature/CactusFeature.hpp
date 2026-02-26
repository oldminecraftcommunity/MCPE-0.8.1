#pragma once
#include <level/gen/feature/Feature.hpp>

struct CactusFeature : public Feature{
	CactusFeature();
	virtual ~CactusFeature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t);
};
