#pragma once
#include <entity/particles/Particle.hpp>

struct BubbleParticle: Particle
{
	BubbleParticle(Level*, ParticleType, const std::string&);
	virtual ~BubbleParticle();
	virtual void tick();
	virtual void init(float, float, float, float, float, float, int32_t);
};
