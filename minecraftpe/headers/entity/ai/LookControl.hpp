#pragma once
#include <_types.h>

struct Mob;
struct Entity;

struct LookControl
{
	Mob* controlledEntity;
	float yawRotationSpeed, pitchRotationSpeed;
	bool_t isLooking;
	char align[3];
	float lookX, lookY, lookZ;

	LookControl(Mob*);
	void setLookAt(Entity*, float, float);
	void setLookAt(float, float, float, float, float);

	virtual void tick();
	virtual ~LookControl();
};
