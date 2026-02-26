#pragma once
#include <level/biome/Biome.hpp>

struct ForestBiome : public Biome{
	ForestBiome();

	virtual ~ForestBiome();
	virtual Feature* getTreeFeature(Random*);
};
