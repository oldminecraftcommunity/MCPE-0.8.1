#pragma once
#include <util/Random.hpp>
struct Biome;
struct PerlinNoise;
struct BiomeSource
{
	float* rainfallNoises;
	float* temperatureNoises;
	float* detailNoises;
	int32_t field_10, field_14, field_18, field_1C;
	Biome** biomes;
	PerlinNoise* rainfallNoise;
	PerlinNoise* perlinNoisePtr2;
	PerlinNoise* detailNoise;
	Random randomInstance1, randomInstance2, randomInstance3;

	BiomeSource(struct Level*);
	BiomeSource();

	virtual ~BiomeSource();
	virtual Biome* getBiome(const struct ChunkPos&);
	virtual Biome* getBiome(int32_t, int32_t);
	virtual float* getTemperatureBlock(int32_t, int32_t, int32_t, int32_t);
	virtual Biome** getBiomeBlock(int32_t, int32_t, int32_t, int32_t);
	virtual Biome** getBiomeBlock(Biome**, int32_t, int32_t, int32_t, int32_t);
};
