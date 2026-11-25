#pragma once
#include <entity/particles/Particle.hpp>

struct HeartParticle: Particle
{
	float field_164;
	HeartParticle(Level* level, ParticleType pt, const std::string& a2)
		: Particle(level, pt, a2) {
		this->maxAliveTime = 16;
		this->noclip = 0;
		this->texture = TextureUVCoordinateSet(0.0f, 0.3125f, 0.0625f, 0.375f, 256, 256);
	}
	virtual ~HeartParticle(){}
	virtual void tick();
	virtual void init(float, float, float, float, float, float, int32_t);
	virtual void render(Tesselator&, float, float, float, float, float, float);
};
