#pragma once
#include <_types.h>
struct Random{
	int32_t seed;
	uint32_t permutations[624];
	int32_t index;
	bool_t haveNextNextGaussian;
	float nextNextGaussian;

	Random(int32_t seed);
	Random(void);
	void init_genrand(uint32_t);
	float nextFloat(void);
	float nextGaussian(void);
	uint32_t genrand_int32(void);
	void setSeed(int64_t);
};
