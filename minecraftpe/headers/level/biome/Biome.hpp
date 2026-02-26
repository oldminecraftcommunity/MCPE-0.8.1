#pragma once
#include <_types.h>
#include <vector>
#include <string>

struct Random;
struct Feature;
struct Color4;
struct MobCategory;

struct Biome{
	struct MobSpawnerData{
		int32_t rarity;
		int32_t mobtype;
		int32_t min, max;

		MobSpawnerData(int32_t, int32_t, int32_t, int32_t);
	};

	std::vector<Biome::MobSpawnerData> monsterVec;
	std::vector<Biome::MobSpawnerData> creatureVec;
	std::vector<Biome::MobSpawnerData> waterCreatureVec;
	char_t* biomeName = 0; //TODO might be not char*
	int32_t color = 0;
	uint8_t topBlock = 0;
	uint8_t fillerBlock = 0;
UNK	int8_t field_32 = 0;
UNK	int8_t field_33 = 0;
	int32_t leafColor = 0;
	float temperature = 0;
	float downfall = 0;

	static Biome* rainForest;
	static Biome* swampland;
	static Biome* seasonalForest;
	static Biome* forest;
	static Biome* savanna;
	static Biome* shrubland;
	static Biome* taiga;
	static Biome* desert;
	static Biome* plains;
	static Biome* iceDesert;
	static Biome* tundra;

	static std::vector<Biome::MobSpawnerData> _emptyMobList;
	static int32_t defaultTotalEnemyWeight;
	static int32_t defaultTotalFriendlyWeight;
	static Biome* map[64][64];
	//TODO statics


	virtual ~Biome(void);
	virtual Feature* getTreeFeature(Random*);
	virtual Feature* getGrassFeature(Random*);
	virtual float getTemperature(void);
	virtual float adjustScale(float);
	virtual float adjustDepth(float);
	virtual Color4 getSkyColor(float);
	virtual std::vector<Biome::MobSpawnerData>* getMobs(const MobCategory&);
	virtual float getCreatureProbability(void);

	Biome(void);
	Biome* clearMobs(bool_t, bool_t, bool_t);
	Biome* setColor(int32_t);
	Biome* setLeafColor(int32_t);
	Biome* setName(const std::string&);
	Biome* setSnowCovered(void);
	Biome* setTemperatureAndDownfall(float, float);

	static void recalc(void);
	static void initBiomes(void);
	static void teardownBiomes(void);
	static Biome* getBiome(float, float);
	static Biome* _getBiome(float, float);
};
