#include <level/biome/TaigaBiome.hpp>
#include <util/Random.hpp>
#include <level/gen/feature/SpruceFeature.hpp>
#include <level/gen/feature/PineFeature.hpp>
TaigaBiome::TaigaBiome() : Biome(){

}
TaigaBiome::~TaigaBiome() {
}
Feature* TaigaBiome::getTreeFeature(Random* a2) {
	if(a2->genrand_int32() % 3) {
		return new SpruceFeature(0);
	} else {
		return new PineFeature();
	}
}
