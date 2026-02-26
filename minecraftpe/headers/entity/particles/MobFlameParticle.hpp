#pragma once
#include <entity/particles/Particle.hpp>

struct MobFlameParticle: Particle
{
	static std::string FLAME_ATLAS;

	float field_164;
	Entity* entity;
	float xOff, yOff, zOff;
	float field_178;
	MobFlameParticle(Level* level, ParticleType pt, const std::string& a2);

	virtual ~MobFlameParticle();
	virtual void tick();
	virtual float getBrightness(float);
	virtual void init(float, float, float, float, float, float, int32_t);
	virtual void setEntity(Entity*);
	virtual void render(Tesselator&, float, float, float, float, float, float);
};
