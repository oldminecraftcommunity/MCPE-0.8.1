#include <level/BiomeSource.hpp>
#include <util/ChunkPos.hpp>
#include <math/noise/PerlinNoise.hpp>
#include <level/biome/Biome.hpp>
#include <level/Level.hpp>
const float BiomeSource::zoom = 2.0f;
const float BiomeSource::tempScale = 0.025f;
const float BiomeSource::downfallScale = 0.05f;
const float BiomeSource::noiseScale = 0.25f;

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
	this->temperatureNoise = new PerlinNoise(&this->randomInstance2, 4);
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
	this->temperatureNoise = 0;
	this->detailNoise = 0;
	this->biomes = new Biome*[256];
}

BiomeSource::~BiomeSource() {
	if(this->rainfallNoise) delete this->rainfallNoise;
	if(this->temperatureNoise) delete this->temperatureNoise;
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
float* BiomeSource::getTemperatureBlock(int32_t a2, int32_t a3, int32_t xSize, int32_t zSize) {
	this->rainfallNoises = this->rainfallNoise->getRegion(this->rainfallNoises, a2, a3, xSize, zSize, BiomeSource::tempScale, BiomeSource::tempScale, BiomeSource::noiseScale);
	this->detailNoises = this->detailNoise->getRegion(this->detailNoises, a2, a3, xSize, zSize, BiomeSource::noiseScale, BiomeSource::noiseScale, 0.588f);
	int index = 0;
	for(int xx = 0; xx < xSize; ++xx) {
		for(int zz = 0; zz < zSize; ++zz) {
			float v16 = 1.0f - ((((this->rainfallNoises[index] * 0.15f) + 0.7f) * 0.99f) + (((this->detailNoises[index] * 1.1f) + 0.5f) * 0.01f));
			float v17 = 1.0f - (v16 * v16);
			if(v17 < 0) v17 = 0;
			if(v17 > 1) v17 = 1;
			this->rainfallNoises[index] = v17;

			++index;
		}
	}
	return this->rainfallNoises;
}
Biome** BiomeSource::getBiomeBlock(int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
	this->biomes = this->getBiomeBlock(this->biomes, a2, a3, a4, a5);
	return this->biomes;
}
Biome** BiomeSource::getBiomeBlock(Biome** biomes, int32_t xStart, int32_t yStart, int32_t xSize, int32_t zSize) {
	this->rainfallNoises = this->rainfallNoise->getRegion(this->rainfallNoises, xStart, yStart, xSize, xSize, BiomeSource::tempScale, BiomeSource::tempScale, BiomeSource::noiseScale);
	this->temperatureNoises = this->temperatureNoise->getRegion(this->temperatureNoises, xStart, yStart, xSize, xSize, BiomeSource::downfallScale, BiomeSource::downfallScale, 0.3333f);
	this->detailNoises = this->detailNoise->getRegion(this->detailNoises, xStart, yStart, xSize, xSize, BiomeSource::noiseScale, BiomeSource::noiseScale, 0.588f);
	int index = 0;
	for(int xx = 0; xx < xSize; ++xx) {
		for(int zz = 0; zz < zSize; ++zz) {
			float v18 = (this->detailNoises[index] * 1.1f) + 0.5f;
			float v21 = (((this->rainfallNoises[index] * 0.15f) + 0.7f) * 0.99f) + (v18 * 0.01f);
			float temp = (((this->temperatureNoises[index] * 0.15f) + 0.5f) * 0.998f) + (v18 * 0.002f);
			float rain = 1.0f - ((1.0f - v21) * (1.0f - v21));
			if(rain < 0) rain = 0;
			if(temp < 0) temp = 0;
			if(rain > 1) rain = 1;
			if(temp > 1) temp = 1;
			this->rainfallNoises[index] = rain;
			this->temperatureNoises[index] = temp;
			this->biomes[index] = Biome::getBiome(rain, temp);
			++index;
		}
	}
	return this->biomes;
}
