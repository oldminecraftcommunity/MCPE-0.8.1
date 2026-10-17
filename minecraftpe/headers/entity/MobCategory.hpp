#pragma once
#include <_types.h>

struct Material;

struct MobCategory{
	static MobCategory monster;
	static MobCategory creature;
	static MobCategory waterCreature;
	static const int32_t numValues;
	static constexpr MobCategory* values[] = {
		&MobCategory::monster, &MobCategory::creature, &MobCategory::waterCreature
	};


	int32_t id;
	int32_t minCountInChunkMaybe;
	int32_t maxCountInChunkMaybe;
	Material* material;
	int8_t field_10;
	char a11, a12, a13;

	MobCategory(int32_t id, int32_t minCnt, int32_t maxCnt, int8_t f10){
		this->id = id;
		this->minCountInChunkMaybe = minCnt;
		this->maxCountInChunkMaybe = maxCnt;
		this->material = 0;
		this->field_10 = f10;
	}
	static void initMobCategories(void);
};
