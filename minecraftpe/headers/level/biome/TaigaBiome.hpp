#pragma once
#include <level/biome/Biome.hpp>
#include <util/Random.hpp>
#include <level/gen/feature/SpruceFeature.hpp>
#include <level/gen/feature/PineFeature.hpp>
struct TaigaBiome : public Biome{
	TaigaBiome() {
	}
	virtual ~TaigaBiome() {
	}
	virtual Feature* getTreeFeature(Random* a2) {
		if(a2->nextInt(3) != 0) {
			return new SpruceFeature(0);
		} else {
			return new PineFeature();
		}
	}
};
