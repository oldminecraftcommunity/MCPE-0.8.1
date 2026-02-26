#pragma once
#include <entity/particles/Particle.hpp>

struct LavaParticle: Particle
{
	float scaleMult;
	LavaParticle(Level* level, ParticleType pt, const std::string& a2);

	virtual ~LavaParticle();
	virtual void tick();
	virtual float getBrightness(float);
	virtual void init(float, float, float, float, float, float, int32_t);
	virtual void render(Tesselator&, float, float, float, float, float, float);
};
