#pragma once
#include <entity/Throwable.hpp>

struct Snowball: Throwable
{
	Snowball(Level* level, Mob* thrower);
	Snowball(Level* level);

	virtual ~Snowball();
	virtual int32_t getEntityTypeId() const;
	virtual void onHit(const HitResult&);
};
