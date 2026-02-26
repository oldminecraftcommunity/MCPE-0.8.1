#include <level/biome/Biome.hpp>
#include <util/Color4.hpp>
#include <entity/MobCategory.hpp>
#include <vector>
#include <string>
#include <string.h>
#include <level/gen/feature/TreeFeature.hpp>
#include <util/Random.hpp>
#include <tile/Tile.hpp>
#include <level/gen/feature/TallgrassFeature.hpp>
#include <level/biome/RainforestBiome.hpp>
#include <level/biome/SwampBiome.hpp>
#include <level/biome/ForestBiome.hpp>
#include <level/biome/FlatBiome.hpp>
#include <level/biome/TaigaBiome.hpp>

Biome* Biome::rainForest;
Biome* Biome::swampland;
Biome* Biome::seasonalForest;
Biome* Biome::forest;
Biome* Biome::savanna;
Biome* Biome::shrubland;
Biome* Biome::taiga;
Biome* Biome::desert;
Biome* Biome::plains;
Biome* Biome::iceDesert;
Biome* Biome::tundra;

std::vector<Biome::MobSpawnerData> Biome::_emptyMobList = {};
int32_t Biome::defaultTotalEnemyWeight = 0;
int32_t Biome::defaultTotalFriendlyWeight = 0;
Biome* Biome::map[64][64];


Biome::MobSpawnerData::MobSpawnerData(int32_t rarity, int32_t mobtype, int32_t min, int32_t max){
	this->rarity = rarity;
	this->mobtype = mobtype;
	this->min = min;
	this->max = max;
}

Biome::~Biome(void){
	if(this->biomeName) delete this->biomeName;
}
Feature* Biome::getTreeFeature(Random* rand){
	rand->genrand_int32(); //must be here
	return new TreeFeature(0, 0);
}
Feature* Biome::getGrassFeature(Random* rand){
	return new TallgrassFeature(Tile::tallgrass->blockID, 1);
}
float Biome::getTemperature(void){
	return this->temperature;
}
float Biome::adjustScale(float f){
	return f;
}
float Biome::adjustDepth(float f){
	return f;
}
Color4 Biome::getSkyColor(float a3){
	float v3;

	v3 = a3 / 3.0f;

	if(v3 < -1.0) v3 = -1.0;
	else if(v3 > 1.0) v3 = 1.0;

	return Color4::fromHSB(0.62222 - (float)(v3 * 0.05), (float)(v3 * 0.1) + 0.5, 1.0);
}
std::vector<Biome::MobSpawnerData>* Biome::getMobs(const MobCategory& cat){
	if(&cat == &MobCategory::monster) return &this->monsterVec;
	if(&cat == &MobCategory::creature) return &this->creatureVec;
	if(&cat == &MobCategory::waterCreature) return &this->waterCreatureVec;

	return &Biome::_emptyMobList;
}
float Biome::getCreatureProbability(void){
	return 0.08f;
}

Biome::Biome(void){
	this->biomeName = 0;
	this->topBlock = Tile::grass->blockID;
	this->fillerBlock = Tile::dirt->blockID;

	this->leafColor = 5169201;
	this->temperature = 0.5f;
	this->downfall = 0.5f;
	this->creatureVec = {};
	this->monsterVec = {};

	this->creatureVec.emplace_back(Biome::MobSpawnerData(12, 13, 2, 3));
	this->creatureVec.emplace_back(Biome::MobSpawnerData(10, 12, 1, 3));
	this->creatureVec.emplace_back(Biome::MobSpawnerData(10, 10, 2, 4));
	this->creatureVec.emplace_back(Biome::MobSpawnerData(8, 11, 2, 3));

	this->monsterVec.emplace_back(Biome::MobSpawnerData(8, 35, 2, 3));
	this->monsterVec.emplace_back(Biome::MobSpawnerData(12, 32, 2, 4));
	this->monsterVec.emplace_back(Biome::MobSpawnerData(6, 34, 1, 3));
	this->monsterVec.emplace_back(Biome::MobSpawnerData(4, 33, 1, 1));

	Biome::defaultTotalEnemyWeight = 0;
	Biome::defaultTotalFriendlyWeight = 0;

	for(int i = 0; i < this->monsterVec.size(); ++i){
		Biome::defaultTotalEnemyWeight += this->monsterVec[i].rarity;
	}

	for(int i = 0; i < this->creatureVec.size(); ++i){
		Biome::defaultTotalFriendlyWeight += this->creatureVec[i].rarity;
	}

}
Biome* Biome::clearMobs(bool_t creature, bool_t water, bool_t monsters){
	if(creature) this->creatureVec.clear();
	if(water) this->waterCreatureVec.clear();
	if(monsters) this->monsterVec.clear();
	return this;
}
Biome* Biome::setColor(int32_t color){
	this->color = color;
	return this;
}
Biome* Biome::setLeafColor(int32_t color){
	this->leafColor = color;
	return this;
}
Biome* Biome::setName(const std::string& str){
	this->biomeName = new char[str.length()+1];
	strcpy(this->biomeName, str.c_str());
	return this;
}
Biome* Biome::setSnowCovered(void){
	return this;
}
Biome* Biome::setTemperatureAndDownfall(float t, float d){
	this->temperature = t;
	this->downfall = d;
	return this;
}

void Biome::recalc(void) {
	for(int32_t i = 0; i != 64; ++i) {
		for(int32_t j = 0; j != 64; ++j) {
			Biome* b = Biome::_getBiome((float)i / 63.0, (float)j / 63.0);
			Biome::map[j][i] = b; //TODO check
		}
	}
	Biome::desert->topBlock = Tile::sand->blockID;
	Biome::desert->fillerBlock = Tile::sand->blockID;
	Biome::iceDesert->topBlock = Tile::sand->blockID;
	Biome::iceDesert->fillerBlock = Tile::sand->blockID;

}
void Biome::initBiomes(void) {
	Biome::rainForest = (new RainforestBiome())->setColor(0x537B09)->setName("Rainforest")->setLeafColor(0x537B09)->setTemperatureAndDownfall(1.2, 0.9); //TODO fill zeros before Biome::Biome()
	Biome::swampland = (new SwampBiome())->setColor(0x7F9B2)->setName("Swampland")->setLeafColor(0x8BAF48)->setTemperatureAndDownfall(0.8, 0.9); //TODO fill zeros
	Biome::seasonalForest = (new Biome())->setColor(0x56621)->setName("Seasonal Forest");
	Biome::forest = (new ForestBiome())->setColor(0x56621)->setName("Forest")->setLeafColor(0x4EBA31)->setTemperatureAndDownfall(0.7, 0.8); //TODO fill zeros
	Biome::savanna = (new FlatBiome())->setColor(0xD9E023)->setName("Savanna")->setTemperatureAndDownfall(0.8, 0.4); //TODO fill zeros
	Biome::shrubland = (new Biome())->setColor(0xA1AD20)->setName("Shrubland");
	Biome::taiga = (new TaigaBiome())->setColor(0xB6659)->setName("Taiga")->setSnowCovered()->setLeafColor(0x4EBA3)->setTemperatureAndDownfall(0.05, 0.8); //TODO fill zeros
	Biome::desert = (new FlatBiome())->setColor(0xFA9418)->clearMobs(1, 1, 0)->setName("Desert")->setTemperatureAndDownfall(2.0, 0.0); //TODO fill zeros
	Biome::plains = (new FlatBiome())->setColor(0x8DB360)->setName("Plains")->setTemperatureAndDownfall(0.8, 0.4); //TOOD fill zeros
	Biome::iceDesert = (new FlatBiome())->setColor(0xFFFFFF)->clearMobs(1, 0, 0)->setName("Ice Desert")->setSnowCovered()->setLeafColor(0xC4D339)->setTemperatureAndDownfall(0.0, 0.5);
	Biome::tundra = (new Biome())->setColor(0x163933)->setName("Tundra")->setSnowCovered()->setLeafColor(0xC4D339)->setTemperatureAndDownfall(0.05, 0.8);
	Biome::recalc();
}
void Biome::teardownBiomes(void) {
	if(Biome::rainForest) {
		delete Biome::rainForest;
	}
	Biome::rainForest = 0;
	if(Biome::swampland) {
		delete Biome::swampland;
	}
	Biome::swampland = 0;
	if(Biome::seasonalForest) {
		delete Biome::seasonalForest;
	}
	Biome::seasonalForest = 0;
	if(Biome::forest) {
		delete Biome::forest;
	}
	Biome::forest = 0;
	if(Biome::savanna) {
		delete Biome::savanna;
	}
	Biome::savanna = 0;
	if(Biome::shrubland) {
		delete Biome::shrubland;
	}
	Biome::shrubland = 0;
	if(Biome::taiga) {
		delete Biome::taiga;
	}
	Biome::taiga = 0;
	if(Biome::desert) {
		delete Biome::desert;
	}
	Biome::desert = 0;
	if(Biome::plains) {
		delete Biome::plains;
	}
	Biome::plains = 0;
	if(Biome::iceDesert) {
		delete Biome::iceDesert;
	}
	Biome::iceDesert = 0;
	if(Biome::tundra) {
		delete Biome::tundra;
	}
	Biome::tundra = 0;
}
Biome* Biome::getBiome(float a1, float a2){
	return Biome::map[(int32_t)(float)(a2 * 63.0)][(int32_t)(float)(a1 * 63.0)];
}

Biome* Biome::_getBiome(float temp, float rain) {
	Biome** v2; // r2
	float newRain; // s14

	if(temp < 0.1) {
		goto LABEL_2;
	}
	newRain = rain * temp;
	if((float)(rain * temp) >= 0.2) {
		if(newRain <= 0.5 || temp >= 0.7) {
			if(temp >= 0.5) {
				if(temp >= 0.97) {
					if(newRain >= 0.45) {
						if(newRain >= 0.9) {
							v2 = &Biome::rainForest;
						} else {
							v2 = &Biome::seasonalForest;
						}
					} else {
						v2 = &Biome::plains;
					}
				} else if(newRain >= 0.35) {
					v2 = &Biome::forest;
				} else {
					v2 = &Biome::shrubland;
				}
			} else {
				v2 = &Biome::taiga;
			}
		} else {
			v2 = &Biome::swampland;
		}
	} else {
		if(temp < 0.5) {
LABEL_2:
			v2 = &Biome::tundra;
			return (*v2);
		}
		if(temp >= 0.95) {
			v2 = &Biome::desert;
		} else {
			v2 = &Biome::savanna;
		}
	}
	return (*v2);
}
