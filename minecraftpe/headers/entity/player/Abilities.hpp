#pragma once
#include <_types.h>
struct CompoundTag;
struct Abilities
{
	bool_t invulnerable;
	bool_t flying;
	bool_t mayfly;
	bool_t instabuild;

	void addSaveData(CompoundTag*);
	void loadSaveData(CompoundTag*);
};
