#pragma once
#include <_types.h>
#include <set>
struct Mob;
struct Entity;

struct Sensing
{
	Mob* holder;
	std::set<int32_t> _canSee;
	std::set<int32_t> _cannotSee;
	Sensing(Mob*);

	bool_t canSee(Entity*);
};
