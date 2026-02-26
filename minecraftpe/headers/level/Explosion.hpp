#pragma once
#include <_types.h>
#include <unordered_set>
#include <util/TilePos.hpp>
#include <util/Random.hpp>

struct Entity;
struct Level;
struct Explosion
{
	float field_0, field_4, field_8, field_C;
	std::unordered_set<TilePos> field_10;
	int32_t field_28, field_2C;
	bool_t field_30;
	int8_t field_31, field_32, field_33;
	Entity* entity;
	Random random;
	Level* level;

	Explosion(Level*, Entity*, float, float, float, float);
	void explode();
	void finalizeExplosion();
};
