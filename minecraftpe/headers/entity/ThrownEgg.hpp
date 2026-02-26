#pragma once
#include <entity/Throwable.hpp>

struct ThrownEgg: Throwable
{
	ThrownEgg(Level* level, Mob* thrower);
	ThrownEgg(Level* level);

	virtual ~ThrownEgg();
	virtual int32_t getEntityTypeId() const;
	virtual void onHit(const HitResult&);
};
