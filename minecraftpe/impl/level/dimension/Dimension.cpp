#include <level/dimension/Dimension.hpp>
#include <level/dimension/NormalDayCycleDimension.hpp>
#include <level/BiomeSource.hpp>
#include <level/Level.hpp>
#include <level/gen/RandomLevelSource.hpp>
#include <math/Mth.hpp>
#include <tile/Tile.hpp>


Dimension::~Dimension() {
	delete this->biomeSourcePtr;
}
void Dimension::init(struct Level* level) {
	this->levelPtr = level;
	this->init();
	this->updateLightRamp();
}

float Dimension::getTimeOfDay(long, float) { //long, float
	return 1.0;
}

float Dimension::getCloudHeight() {
	return 128;
}

void Dimension::updateLightRamp(void) {
	int32_t i;	// r3
	int32_t v2; // s8

	for(i = 0; i != 16; ++i) {
		v2 = i;
		this->lightRamp[i] = (float)((float)((float)(1.0 - (float)(1.0 - (float)((float)v2 * 0.0625))) / (float)((float)((float)(1.0 - (float)((float)v2 * 0.0625)) * 3.0) + 1.0)) * 0.95) + 0.15;
	}
}

bool_t Dimension::mayRespawn(void) {
	return 1;
}

struct ChunkSource* Dimension::createRandomLevelSource(void) {
	int32_t seed;		  // r7
	LevelData* levelData; // r0
	int32_t genVer;		  // r6
	Level* level;		  // r0
	bool_t spawnMobs;	  // r5

	seed = this->levelPtr->getSeed();
	levelData = this->levelPtr->getLevelData();
	genVer = levelData->getGeneratorVersion();
	level = this->levelPtr;
	if(level->isClient) {
		spawnMobs = 0;
	} else {
		spawnMobs = level->getLevelData()->getSpawnMobs();
	}

	return new RandomLevelSource(this->levelPtr, seed, genVer, spawnMobs);
}

bool_t Dimension::isValidSpawn(int32_t x, int32_t z) {
	int32_t topTile; // r0
	topTile = this->levelPtr->getTopTile(x, z);
	if(topTile == Tile::invisible_bedrock->blockID) {
		return 0;
	} else {
		return Tile::tiles[topTile]->isSolidRender();
	}
}

void Dimension::init() {
	this->biomeSourcePtr = new BiomeSource(this->levelPtr);
}

Color4 Dimension::getFogColor(float a3, float a4) {
	float v = Mth::cos((a3 * Mth::PI) * 2);
	float v5 = 0.5f + v*2;
	if(v5 > 1.0f) v5 = 1.0f;
	if(v5 <= 0.0f) v5 = 0.0f;

	float v6 = (v5 * 0.94f) + 0.06f;
	return Color4(v6 * 0.50196f, v6 * 0.8549f, v6, 1);
}


Color4 Dimension::getSunriseColor(float a3, float a4) {
	float v4 = Mth::cos((a3 * Mth::PI)*2);
	if(v4 >= -0.4f && v4 <= 0.4f) {
		//TODO inlined stuff
		float v5 = (float)((float)((float)(v4 + 0.0f) / 0.4f) * 0.5f) + 0.5f;
		float v6 = 1.0f - (float)((float)(1.0f - Mth::sin((float)(v5 * Mth::PI))) * 0.99f);
		float v7 = (float)(v5 * 0.3f) + 0.7f;
		float v8 = v5 * v5;
		return Color4(v7, (float)(v8 * 0.7f) + 0.2f, (float)(v8 * 0.0f) + 0.2f, v6 * v6);
	}
	return Color4(0, 0, 0, 0);
}

Dimension::Dimension() {
	this->biomeSourcePtr = 0;
	this->field_C = 0;
	this->isOverworldMaybe = 0;
	this->hasNoSkyMaybe = 0;
	this->id = 0;
}
int32_t Dimension::getMoonPhase(long a2) {
	return a2 / 19200 % 8;
}
Dimension* Dimension::getNew(int32_t id) {
	if(id == 10) {
		return new NormalDayCycleDimension();
	} else if(id == 0) {
		return new Dimension();
	}
	return 0;
}
