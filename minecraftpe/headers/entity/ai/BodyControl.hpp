#pragma once
#include <_types.h>

struct Mob;
struct BodyControl
{
	Mob* controlledEntity;
	int32_t field_4;
	float field_8;

	BodyControl(Mob*);
	void clientTick();
};
