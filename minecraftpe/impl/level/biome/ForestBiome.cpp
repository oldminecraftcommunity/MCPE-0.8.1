#include <level/biome/ForestBiome.hpp>
#include <util/Random.hpp>
#include <level/gen/feature/TreeFeature.hpp>
#include <level/gen/feature/BirchFeature.hpp>

ForestBiome::ForestBiome(){

}

ForestBiome::~ForestBiome() {
}
Feature* ForestBiome::getTreeFeature(Random* a2) {
	if(a2->genrand_int32() % 5) {
		a2->genrand_int32();
		return new TreeFeature(0, 0);
	}
	return new BirchFeature(0);
}
