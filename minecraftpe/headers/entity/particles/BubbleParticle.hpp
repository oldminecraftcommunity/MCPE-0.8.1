#pragma once
#include <entity/particles/Particle.hpp>
#include <math/Mth.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

struct BubbleParticle: Particle
{
	BubbleParticle(Level* level, ParticleType pt, const std::string& a2)
		: Particle(level, pt, a2) {
		this->rColMul = 1;
		this->gColMul = 1;
		this->bColMul = 1;
		this->setSize(0.02, 0.02);
		this->texture = TextureUVCoordinateSet(0.0f, 0.125f, 0.0625f, 0.1875f, 256, 256);
	}
	virtual ~BubbleParticle() {
	}
	virtual void tick() {
		this->prevX = this->posX;
		this->prevY = this->posY;
		this->prevZ = this->posZ;
		this->motionY += 0.002f;
		this->move(this->motionX, this->motionY, this->motionZ);

		this->motionX *= 0.85f;
		this->motionY *= 0.85f;
		this->motionZ *= 0.85f;
		if (this->level->getMaterial(Mth::floor(this->posX), Mth::floor(this->posY), Mth::floor(this->posZ)) != Material::water) {
			this->remove();
		}
		int maxAliveTime = this->maxAliveTime;
		this->maxAliveTime -= 1;
		if (maxAliveTime <= 0) {
			this->remove();
		}
	}
	virtual void init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
		float scale = this->_scale;
		float mult = Entity::sharedRandom.nextFloat();
		this->_scale = scale * ((mult * 0.6f) + 0.2f);

		this->motionX = (a5 * 0.2f) + (((Mth::random() * 2) - 1.0f) * 0.02f);
		this->motionY = (a6 * 0.2f) + (((Mth::random() * 2) - 1.0f) * 0.02f);
		this->motionZ = (a7 * 0.2f) + (((Mth::random() * 2) - 1.0f) * 0.02f);

		this->maxAliveTime = (int) ((8.0f / (Mth::random() * 0.8 + 0.2))); //0.8 and 0.2 must be a double
	}
};
