#pragma once
#include <entity/particles/Particle.hpp>
#include <math/Mth.hpp>

struct RedDustParticle: Particle
{
	float field_164;
	RedDustParticle(Level* level, ParticleType pt, const std::string& a2)
		: Particle(level, pt, a2) {
		this->noclip = 0;
	}

	virtual ~RedDustParticle(){}
	virtual void tick() {
		int maxAliveTime = this->maxAliveTime;
		this->prevX = this->posX;
		this->prevY = this->posY;
		this->prevZ = this->posZ;
		int ticksAlive = this->ticksAlive;
		this->ticksAlive += 1;
		if(ticksAlive >= maxAliveTime) {
			this->remove();
		}
		this->texture = TextureUVCoordinateSet::fromOldSystem(-8 * this->ticksAlive / this->maxAliveTime + 7);
		this->move(this->motionX, this->motionY, this->motionZ);
		if(this->posY == this->prevY) {
			this->motionX *= 1.1f;
			this->motionZ *= 1.1f;
		}

		this->motionX *= 0.96f;
		this->motionY *= 0.96f;
		this->motionZ *= 0.96f;
		if(this->onGround) {
			this->motionX *= 0.7f;
			this->motionZ *= 0.7f;
		}
	}
	virtual void init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
		float v8;	 // s14
		int32_t v10; // r5
		float v11;	 // s16
		float v12;	 // r0
		float v13;	 // s15

		v8 = this->motionX * 0.1;
		this->rColMul = 1.0;
		this->bColMul = 0.0;
		this->gColMul = 0.0;
		v10 = a8;
		if(!a8) {
			v10 = 1;
		}
		this->motionX = v8;
		this->motionY = this->motionY * 0.1;
		this->motionZ = this->motionZ * 0.1;
		v11 = (float)(Mth::random() * 0.4) + 0.6;
		this->rColMul = (float)((float)((float)(Mth::random() * 0.2) + 0.8) * this->rColMul) * v11;
		this->gColMul = (float)((float)((float)(Mth::random() * 0.2) + 0.8) * this->gColMul) * v11;
		v12 = Mth::random();
		v13 = (float)(this->_scale * 0.75) * (float)v10;
		this->bColMul = (float)((float)((float)(v12 * 0.2) + 0.8) * this->bColMul) * v11;
		this->_scale = v13;
		this->field_164 = v13;
		this->maxAliveTime = v10 * (int32_t)(8.0 / (Mth::random() * 0.8 + 0.2));
	}
	virtual void render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
		float v8; // s15

		v8 = (float)((float)((float)this->ticksAlive + a3) / (float)this->maxAliveTime) * 32.0;
		if(v8 < 0.0) {
			v8 = 0.0;
		} else if(v8 > 1.0) {
			v8 = 1.0;
		}
		this->_scale = this->field_164 * v8;
		Particle::render(a2, a3, a4, a5, a6, a7, a8);
	}
};
