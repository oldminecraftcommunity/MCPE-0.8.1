#pragma once
#include <_types.h>
#include "Synth.hpp"
#include <util/Random.hpp>

struct ImprovedNoise;

struct PerlinNoise : public Synth{
	//TODO fields
	ImprovedNoise** octaves;
	int32_t octavesAmount;
	Random randomSelf;
	Random* randomPtr;

	PerlinNoise(int32_t);
	PerlinNoise(Random*, int32_t);
	virtual ~PerlinNoise(void);
	int32_t hashCode(void);
	void init(int32_t);
	virtual float getValue(float, float);
	float getValue(float, float, float);
	float* getRegion(float*, float, float, float, int32_t, int32_t, int32_t, float, float, float);
	float* getRegion(float*, int32_t, int32_t, int32_t, int32_t, float, float, float);
};
