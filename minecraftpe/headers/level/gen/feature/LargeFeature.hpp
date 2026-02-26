#pragma once
#include <_types.h>
#include <util/Random.hpp>

struct ChunkSource;
struct Level;

struct LargeFeature{

	int32_t range;
	Random random;

	LargeFeature(void);

	virtual ~LargeFeature();
	virtual void apply(ChunkSource*, Level*, int32_t, int32_t, uint8_t*, int32_t);
	virtual void addFeature(Level*, int32_t, int32_t, int32_t, int32_t, uint8_t*, int32_t) = 0;
};
