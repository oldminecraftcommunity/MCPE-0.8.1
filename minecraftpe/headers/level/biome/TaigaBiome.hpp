#pragma once
#include <level/biome/Biome.hpp>

struct TaigaBiome : public Biome{
	TaigaBiome();
	virtual ~TaigaBiome();
	virtual Feature* getTreeFeature(Random*);
};
