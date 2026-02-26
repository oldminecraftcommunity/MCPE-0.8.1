#pragma once
#include <entity/particles/Particle.hpp>

struct ExplodeParticle: Particle
{
	ExplodeParticle(Level* level, ParticleType pt, const std::string& a2);

	virtual ~ExplodeParticle();
	virtual void tick();
	virtual void init(float, float, float, float, float, float, int32_t);
};
