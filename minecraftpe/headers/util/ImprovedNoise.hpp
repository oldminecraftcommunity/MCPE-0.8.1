#pragma once
#include <_types.h>
#include "Synth.hpp"
#include "Random.hpp"

#define FADE(x) (x*x*x*(x*(x*6 - 15) + 10))

struct ImprovedNoise : public Synth{
UNK	byte		field_4;
UNK	byte		field_5;
UNK	byte		field_6;
UNK	byte		field_7;
	float		xCoord;
	float		yCoord;
	float		zCoord;
	int32_t		permutations[512];

	ImprovedNoise(Random*);
	ImprovedNoise(void);
	virtual ~ImprovedNoise(void);
	void init(Random*);
	float lerp(float, float, float);
	float grad(int32_t, float, float, float);
	float grad2(int32_t, float, float);
	float noise(float, float, float);
	virtual float getValue(float, float);
	float getValue(float, float, float);
	void add(float*, float, float, float, int32_t, int32_t, int32_t, float, float, float, float);
	int32_t hashCode(void);
};
