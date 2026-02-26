#pragma once
#include <entity/particles/Particle.hpp>

struct BreakingItemParticle: Particle
{
	struct Item* item;
	BreakingItemParticle(Level*, ParticleType, const std::string&, Item* it);

	virtual ~BreakingItemParticle();
	virtual void init(float, float, float, float, float, float, int32_t);
	virtual void render(Tesselator&, float, float, float, float, float, float);
};
