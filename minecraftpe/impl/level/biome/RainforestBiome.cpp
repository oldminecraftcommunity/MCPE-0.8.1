#include <level/biome/RainforestBiome.hpp>
#include <level/gen/feature/TreeFeature.hpp>
#include <util/Random.hpp>

RainforestBiome::RainforestBiome() : Biome(){

}

RainforestBiome::~RainforestBiome() {
}
Feature* RainforestBiome::getTreeFeature(Random* a2) {
	a2->genrand_int32(); //very needed to preserve vanilla feature generation
	return new TreeFeature(0, 0);
}
