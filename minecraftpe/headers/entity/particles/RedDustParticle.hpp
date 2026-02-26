#pragma once
#include <entity/particles/Particle.hpp>

struct RedDustParticle: Particle
{
	float field_164;
	RedDustParticle(Level* level, ParticleType pt, const std::string& a2);

	virtual ~RedDustParticle();
	virtual void tick();
	virtual void init(float, float, float, float, float, float, int32_t);
	virtual void render(Tesselator&, float, float, float, float, float, float);
};
