#pragma once
#include <_types.h>
#include <math/Pos.hpp>
#include <map>

struct ChunkPos;
struct Level;
struct Mob;
struct MobCategory;
struct Biome;
struct Random;

struct MobSpawner
{
	static std::map<ChunkPos, bool> chunksToPoll;
	static bool addMob(Level*, Mob*, float, float, float, float, float, bool_t);
	static void finalizeMobSettings(Mob*, Level*, float, float, float);
	static Pos getRandomPosWithin(Level*, int32_t, int32_t);
	static bool_t isSpawnPositionOk(const MobCategory&, Level*, int32_t, int32_t, int32_t);
	static void makeBabyMob(Mob*, float);
	static void postProcessSpawnMobs(Level*, Biome*, int32_t, int32_t, int32_t, int32_t, Random*);
	static bool_t tick(Level*, bool_t, bool_t);
};
