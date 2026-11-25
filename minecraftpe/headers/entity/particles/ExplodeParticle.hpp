#pragma once
#include <entity/particles/Particle.hpp>
#include <math/Mth.hpp>

struct ExplodeParticle: Particle
{
	ExplodeParticle(Level* level, ParticleType pt, const std::string& a2)
		: Particle(level, pt, a2) {
		this->noclip = 0;
	}

	virtual ~ExplodeParticle() {
	}
	virtual void tick() {
		int maxAliveTime = this->maxAliveTime;

		this->prevX = this->posX;
		this->prevY = this->posY;
		this->prevZ = this->posZ;

		int ticksAlive = this->ticksAlive;
		this->ticksAlive += 1;
		if (ticksAlive >= maxAliveTime) {
			this->remove();
		}
		this->texture = TextureUVCoordinateSet::fromOldSystem(-8 * this->ticksAlive / this->maxAliveTime + 7);
		this->motionY += 0.004f;
		this->move(this->motionX, this->motionY, this->motionZ);

		this->motionX *= 0.9f;
		this->motionY *= 0.9f;
		this->motionZ *= 0.9f;

		if (this->onGround) {
			this->motionX *= 0.7f;
			this->motionZ *= 0.7f;
		}
	}
	virtual void init(float xPos, float yPos, float zPos, float motX, float motY, float motZ, int32_t a8) {
		this->motionX = motX + ((Mth::random() * 2) - 1.0f) * 0.05f;
		this->motionY = motY + ((Mth::random() * 2) - 1.0f) * 0.05f;
		this->motionZ = motZ + ((Mth::random() * 2) - 1.0f) * 0.05f;
		this->rColMul = this->gColMul = this->bColMul = (Entity::sharedRandom.nextFloat() * 0.3f) + 0.7f;
		this->_scale = ((Entity::sharedRandom.nextFloat() * Entity::sharedRandom.nextFloat()) * 6.0f) + 1.0f;
		this->maxAliveTime = (int32_t) (16.0f / ((Entity::sharedRandom.nextFloat() * 0.8f) + 0.2f)) + 2;
	}
};
