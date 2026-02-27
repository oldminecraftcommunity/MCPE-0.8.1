#pragma once
#include <_types.h>

struct Material;

struct MobCategory{
	static MobCategory monster;
	static MobCategory creature;
	static MobCategory waterCreature;
	static int32_t numValues;
	static MobCategory* values[];

	int32_t id;
	int32_t minCountInChunkMaybe;
	int32_t maxCountInChunkMaybe;
	Material* material;
	int8_t field_10;
	char a11, a12, a13;

	MobCategory(int32_t, int32_t, int32_t, int8_t);

	static void initMobCategories(void);
};
