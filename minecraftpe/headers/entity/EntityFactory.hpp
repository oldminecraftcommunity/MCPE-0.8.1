#pragma once
#include <_types.h>

struct Entity;
struct Level;
struct CompoundTag;

struct EntityFactory
{
	static Entity* CreateEntity(int32_t type, Level* level);
	static Entity* loadEntity(CompoundTag* tag, Level* level);
};
