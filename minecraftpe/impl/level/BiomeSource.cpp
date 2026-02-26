#include <level/BiomeSource.hpp>
#include <util/ChunkPos.hpp>
#include <util/PerlinNoise.hpp>
#include <level/biome/Biome.hpp>
#include <level/Level.hpp>

BiomeSource::BiomeSource(struct Level* a2)
	: randomInstance1(9871 * a2->getSeed())
	, randomInstance2(39811 * a2->getSeed())
	, randomInstance3(543321 * a2->getSeed()) {
	this->rainfallNoises = 0;
	this->temperatureNoises = 0;
	this->detailNoises = 0;
	this->field_10 = 0;
	this->field_14 = 0;
	this->field_18 = 0;
	this->field_1C = 0;
	this->biomes = 0;
	this->rainfallNoise = new PerlinNoise(&this->randomInstance1, 4);
	this->perlinNoisePtr2 = new PerlinNoise(&this->randomInstance2, 4);
	this->detailNoise = new PerlinNoise(&this->randomInstance3, 2);
	this->biomes = new Biome*[256];
	this->rainfallNoises = new float[256];
}
BiomeSource::BiomeSource() {
	this->rainfallNoises = 0;
	this->temperatureNoises = 0;
	this->detailNoises = 0;
	this->field_10 = 0;
	this->field_14 = 0;
	this->field_18 = 0;
	this->field_1C = 0;
	this->biomes = 0;
	this->rainfallNoise = 0;
	this->perlinNoisePtr2 = 0;
	this->detailNoise = 0;
	this->biomes = new Biome*[256];
}

BiomeSource::~BiomeSource() {
	if(this->rainfallNoise) delete this->rainfallNoise;
	if(this->perlinNoisePtr2) delete this->perlinNoisePtr2;
	if(this->detailNoise) delete this->detailNoise;
	if(this->rainfallNoises) delete[] this->rainfallNoises;
	if(this->temperatureNoises) delete[] this->temperatureNoises;
	if(this->detailNoises) delete[] this->detailNoises;
	if(this->biomes) delete[] this->biomes;
}
Biome* BiomeSource::getBiome(const ChunkPos& a2) {
	return this->getBiome(16 * a2.x, 16 * a2.z);
}
Biome* BiomeSource::getBiome(int32_t x, int32_t z) {
	return *this->getBiomeBlock(x, z, 1, 1);
}
float* BiomeSource::getTemperatureBlock(int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
	float* reg; // r0
	float* detailNoises; // r1
	float* v11; // r0
	int32_t v12; // r2
	int32_t v13; // r3
	int32_t v14; // r12
	float* v15; // r0
	float v16; // s15
	float v17; // s15
	int32_t i; // r1

	reg = this->rainfallNoise->getRegion(this->rainfallNoises, a2, a3, a4, a5, 0.025, 0.025, 0.25);
	detailNoises = this->detailNoises;
	this->rainfallNoises = reg;
	v11 = this->detailNoise->getRegion(detailNoises, a2, a3, a4, a5, 0.25, 0.25, 0.588);
	v12 = 0;
	v13 = 0;
	this->detailNoises = v11;
	while(v12 < a4) {
		for(i = 0; i < a5; ++i) {
			v14 = i + v13;
			v15 = &this->rainfallNoises[v14];
			v16 = 1.0 - (float)((float)((float)((float)(this->detailNoises[v14] * 1.1) + 0.5) * 0.01) + (float)((float)((float)(*v15 * 0.15) + 0.7) * 0.99));
			v17 = 1.0 - (float)(v16 * v16);
			if(v17 < 0.0) {
				v17 = 0.0;
			} else if(v17 > 1.0) {
				v17 = 1.0;
			}
			*v15 = v17;
		}
		if(a5 >= 0) {
			v13 += a5;
		}
		++v12;
	}
	return this->rainfallNoises;
}
Biome** BiomeSource::getBiomeBlock(int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
	this->biomes = this->getBiomeBlock(this->biomes, a2, a3, a4, a5);
	return this->biomes;
}
Biome** BiomeSource::getBiomeBlock(Biome** biomes, int32_t a3, int32_t a4, int32_t a5, int32_t a6){
	float* reg;				  // r0
	float* temperatureNoises; // r1
	float* reg2;			  // r0
	int32_t v12;			  // r2
	int32_t v13;			  // r6
	int32_t v14;			  // r8
	float* detailNoises;	  // r1
	int32_t v16;			  // r10
	int32_t v17;			  // r7
	float v18;				  // s14
	float* v19;				  // r1
	float v20;				  // s15
	float v21;				  // s14
	float v22;				  // s14
	Biome** biomes2;		  // r11

	reg = this->rainfallNoise->getRegion(this->rainfallNoises, a3, a4, a5, a5, 0.025, 0.025, 0.25);
	temperatureNoises = this->temperatureNoises;
	this->rainfallNoises = reg;
	reg2 = this->perlinNoisePtr2->getRegion(temperatureNoises, a3, a4, a5, a5, 0.05, 0.05, 0.3333);
	v12 = a3;
	v13 = 0;
	v14 = 0;
	detailNoises = this->detailNoises;
	this->temperatureNoises = reg2;
	this->detailNoises = this->detailNoise->getRegion(detailNoises, v12, a4, a5, a5, 0.25, 0.25, 0.588);
	while(v13 < a5) {
		v17 = 0;
		while(v17 < a6) {
			v16 = v17 + v14;
			++v17;
			v18 = (float)(this->detailNoises[v16] * 1.1) + 0.5;
			v19 = &this->rainfallNoises[v16];
			v20 = (float)(v18 * 0.002) + (float)((float)((float)(this->temperatureNoises[v16] * 0.15) + 0.5) * 0.998);
			v21 = 1.0 - (float)((float)(v18 * 0.01) + (float)((float)((float)(*v19 * 0.15) + 0.7) * 0.99));
			v22 = 1.0 - (float)(v21 * v21);
			if(v22 < 0.0) {
				v22 = 0.0;
			}
			if(v20 < 0.0) {
				v20 = 0.0;
			}
			if(v22 > 1.0) {
				v22 = 1.0;
			}
			*v19 = v22;
			if(v20 > 1.0) {
				v20 = 1.0;
			}
			this->temperatureNoises[v16] = v20;
			biomes2 = this->biomes;
			biomes2[v16] = Biome::getBiome(v22, v20);
		}
		if(a6 >= 0) {
			v14 += a6;
		}
		++v13;
	}
	return this->biomes;
}
