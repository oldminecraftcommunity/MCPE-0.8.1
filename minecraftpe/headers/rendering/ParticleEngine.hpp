#pragma once
#include <_types.h>
#include <deque>
#include <util/Random.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <entity/particles/ParticleType.hpp>

struct Particle;
struct Level;
struct Textures;
struct Entity;
struct ParticleEngine
{
	std::deque<Particle*> particles[16];
	Level* level;
	int8_t field_284, field_285, field_286, field_287;
	int8_t field_288, field_289, field_28A, field_28B;
	int8_t field_28C, field_28D, field_28E, field_28F;
	int8_t field_290, field_291, field_292, field_293;
	std::unordered_map<std::string, std::vector<Particle*>> string2ParticleVec;
	Textures* textures;
	Random random;

	ParticleEngine(Level*, Textures*);
	Particle* _get(ParticleType);
	void _release(Particle*);
	void clear();
	std::string countParticles(); //TODO check return type
	void crack(int32_t, int32_t, int32_t, int32_t);
	Particle* create(ParticleType);
	void destroy(int32_t, int32_t, int32_t);
	Particle* instance(ParticleType, float, float, float, float, float, float, int32_t);
	void render(Entity*, float);
	void setLevel(Level*);
	void tick();
	~ParticleEngine();

};
