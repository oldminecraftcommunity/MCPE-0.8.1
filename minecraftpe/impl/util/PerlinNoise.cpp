#include <util/PerlinNoise.hpp>
#include <util/ImprovedNoise.hpp>
#include <util/Random.hpp>
#include <stdio.h>

PerlinNoise::PerlinNoise(int32_t octaves){
	this->randomPtr = &this->randomSelf;
	this->init(octaves);
}
PerlinNoise::PerlinNoise(Random* random, int32_t octaves){
	this->randomPtr = random;
	this->init(octaves);
}
PerlinNoise::~PerlinNoise(void){
	int32_t v2 = 0;

	while(1){
		if(v2 >= this->octavesAmount) break;

		ImprovedNoise* noise = this->octaves[v2];
		if(noise) delete noise;
		++v2;
	}

	if(this->octaves) delete[] this->octaves;
}
int32_t PerlinNoise::hashCode(void){
	int32_t index, hashCode;

	index = 0;
	hashCode = 4711;

	while(index < this->octavesAmount){
		ImprovedNoise* n = this->octaves[index];
		++index;
		hashCode *= n->hashCode();
	}

	return hashCode;
}
void PerlinNoise::init(int32_t octaves){
	this->octavesAmount = octaves;
	int32_t cntr = 0;
	this->octaves = new ImprovedNoise* [octavesAmount];

	while(cntr < octaves){
		ImprovedNoise* noise = new ImprovedNoise(this->randomPtr);
		this->octaves[cntr] = noise;
		++cntr;
	}
}

float PerlinNoise::getValue(float x, float y){
	float v4;
	int32_t v6;
	float v8;
	float v10;

	v4 = 0;
	v6 = 0;
	v8 = 1.0;

	while(v6 < this->octavesAmount){
		ImprovedNoise* noise = this->octaves[v6];
		++v6;

		v10 = noise->getValue(x * v8, y * v8) / v8;
		v8 = v8 * 0.5;
		v4 = v4 + v10;
	}

	return v4;
}

float PerlinNoise::getValue(float x, float y, float z){
	float v5;
	int32_t index;
	float v10;
	float v12;

	v5 = 0;
	index = 0;
	v10 = 1.0;

	while(index < this->octavesAmount){
		ImprovedNoise* noise = this->octaves[index];
		++index;
		v12 = noise->getValue(x * v10, y * v10, z * v10) / v10;
		v10 = v10 * 0.5;
		v5 = v5 + v12;
	}

	return v5;
}
float* PerlinNoise::getRegion(float* array, float a3, float a4, float a5, int32_t a6, int32_t a7, int32_t a8, float a9, float a10, float a11){
	int32_t totalSize;
	float* arrayPtr;
	int32_t i, octaveIndex;
	float v19;
	ImprovedNoise* octave;

	totalSize = a8*a7*a6;
	if(!array) array = new float[totalSize];
	arrayPtr = array;

	for(i = 0; i < totalSize; ++i){
		arrayPtr[i] = 0;
	}

	octaveIndex = 0;
	v19 = 1;
	while(octaveIndex < this->octavesAmount){
		octave = this->octaves[octaveIndex];
		++octaveIndex;

		octave->add(array, a3, a4, a5, a6, a7, a8, a9*v19, a10*v19, a11*v19, v19);
		v19 = v19 * 0.5;
	}

	return array;
}
float* PerlinNoise::getRegion(float* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, float a7, float a8, float a9){
	return this->getRegion(a2, a3, 10, a4, a5, 1, a6, a7, 1.0, a8);
}
