#pragma once
#include <entity/particles/Particle.hpp>

struct TerrainParticle: Particle
{
	struct Tile* tile;
	TextureUVCoordinateSet field_168;
	TerrainParticle(Level* level, ParticleType pt, const std::string& a2);

	virtual ~TerrainParticle();
	virtual void init(float, float, float, float, float, float, int32_t);
	virtual void render(Tesselator&, float, float, float, float, float, float);
};
