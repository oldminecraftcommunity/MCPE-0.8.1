#pragma once
#include <_types.h>
#include <unordered_set>
#include <util/TilePos.hpp>
#include <util/Random.hpp>

struct Entity;
struct Level;
struct Explosion
{
	float x, y, z, radius;
	std::unordered_set<TilePos> affectedTiles;
	int32_t field_28, field_2C;
	bool_t setFire;
	Entity* entity;
	Random random;
	Level* level;

	Explosion(Level*, Entity*, float, float, float, float);
	void explode();
	void finalizeExplosion();
};
