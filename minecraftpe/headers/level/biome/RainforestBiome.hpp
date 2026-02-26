#pragma once
#include <level/biome/Biome.hpp>

struct RainforestBiome : public Biome{
	RainforestBiome();

	virtual ~RainforestBiome();
	virtual Feature* getTreeFeature(Random*);
};
