#pragma once
#include <level/gen/feature/LargeFeature.hpp>

struct LargeCaveFeature : public LargeFeature{

	virtual ~LargeCaveFeature();
	virtual void addFeature(Level*, int32_t, int32_t, int32_t, int32_t, uint8_t*, int32_t);
	void addTunnel(int32_t, int32_t, uint8_t*, float, float, float, float, float, float, int32_t, int32_t, float);
};
