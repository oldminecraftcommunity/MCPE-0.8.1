#pragma once
#include <_types.h>

struct Mob;

struct JumpControl
{
	Mob* controlledEntity;
	bool_t isJumping;
	char align[3];

	JumpControl(Mob*);
	void jump();

	virtual void tick();
	virtual ~JumpControl();
};
