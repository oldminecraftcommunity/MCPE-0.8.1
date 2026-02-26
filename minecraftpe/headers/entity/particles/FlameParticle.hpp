#pragma once
#include <entity/particles/Particle.hpp>

struct FlameParticle: Particle
{
	float field_164;
	FlameParticle(Level* level, ParticleType pt, const std::string& a2);

	virtual ~FlameParticle();
	virtual void tick();
	virtual float getBrightness(float);
	virtual void init(float, float, float, float, float, float, int32_t);
	virtual void render(Tesselator&, float, float, float, float, float, float);
};
