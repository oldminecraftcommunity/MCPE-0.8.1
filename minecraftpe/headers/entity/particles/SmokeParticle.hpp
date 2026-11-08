#pragma once
#include <entity/particles/Particle.hpp>
#include <math/Mth.hpp>

struct SmokeParticle: Particle
{
	float field_164;
	SmokeParticle(Level* level, ParticleType pt, const std::string& a2)
		: Particle(level, pt, a2) {
		this->noclip = 0;
	}

	virtual ~SmokeParticle() {
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

		this->motionY += 0.004f;
		this->move(this->motionX, this->motionY, this->motionZ);
		if (this->posY == this->prevY) {
			this->motionX *= 1.1f;
			this->motionZ *= 1.1f;
		}

		this->motionX *= 0.96f;
		this->motionY *= 0.96f;
		this->motionZ *= 0.96f;
		if (this->onGround) {
			this->motionX *= 0.7f;
			this->motionZ *= 0.7f;
		}
	}
	virtual void init(float xPos, float yPos, float zPos, float motX, float motY, float motZ, int32_t a8) {
		int32_t v9; // r3
		v9 = a8;
		if (a8 == 0) {
			v9 = 100;
		}
		float v11 = v9 / 100.0f;
		this->motionX = motX + (this->motionX * 0.1f);
		this->motionZ = motZ + (this->motionZ * 0.1f);
		this->motionY = motY + (this->motionY * 0.1f);

		this->rColMul = this->gColMul = this->bColMul = Mth::random() * 0.5f;
		this->field_164 = this->_scale = (this->_scale * 0.75f) * v11;
		this->maxAliveTime = (int32_t) ((v11 * 8.0f) / ((Mth::random() * 0.8f) + 0.2f));
	}
	virtual void render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
		float v12; // s16
		v12 = (float) (((float) (((float) (this->ticksAlive) + a3)) / (float) (this->maxAliveTime))) * 32.0;
		if (v12 < 0.0) {
			v12 = 0.0;
		} else if (v12 > 1.0) {
			v12 = 1.0;
		}

		this->texture = TextureUVCoordinateSet::fromOldSystem(-8 * this->ticksAlive / this->maxAliveTime + 7);
		this->_scale = this->field_164 * v12;
		Particle::render(a2, a3, a4, a5, a6, a7, a8);
	}
};
