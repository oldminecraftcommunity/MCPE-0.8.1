#pragma once
#include <entity/Entity.hpp>
#include <rendering/TextureUVCoordinateSet.hpp>
#include <entity/particles/ParticleType.hpp>

struct Tesselator;
struct Particle: Entity
{
	static std::string ITEMS_ATLAS, TERRAIN_ATLAS, PARTICLE_ATLAS;
	static Vec3 playerViewDir;
	static float zOff, yOff, xOff;

	float coordMultiplier;
	int32_t maxAliveTime;
	TextureUVCoordinateSet texture;
	float field_138, field_13C;
	int32_t ticksAlive;
	float _scale;
	float gravity;
	float rColMul, gColMul, bColMul;
	ParticleType type;
	std::string textureAtlas;

	Particle(Level*, ParticleType, const std::string&);
	void _init(float, float, float, float, float, float, int32_t);
	void scale(float);
	Particle* setPower(float);

	virtual ~Particle();
	virtual void tick();
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual void init(float, float, float, float, float, float, int32_t) = 0;
	virtual void setEntity(Entity*);
	virtual void render(Tesselator&, float, float, float, float, float, float);
};
