#pragma once
#include <_types.h>
#include <string>
struct Mob;
struct Level;

struct MobFactory
{
	static Mob* CreateMob(int32_t type, Level* level);
	static std::string GetMobNameID(int32_t type);
	static Mob* getStaticTestMob(int32_t, Level*);
};
