#include <entity/particles/HeartParticle.hpp>
HeartParticle::HeartParticle(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->maxAliveTime = 16;
	this->noclip = 0;
	this->texture = {0, 0.3125, 0.0625, 0.375, 256, 256};
}

HeartParticle::~HeartParticle() {
}
void HeartParticle::tick() {
	int32_t maxAliveTime; // r2
	int32_t ticksAlive;	  // r3
	bool_t onGround;	  // r3
	float v5;			  // s13
	float v6;			  // s15

	maxAliveTime = this->maxAliveTime;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;
	ticksAlive = this->ticksAlive;
	this->ticksAlive = ticksAlive + 1;
	if(ticksAlive >= maxAliveTime) {
		this->remove();
	}
	this->move(this->motionX, this->motionY, this->motionZ);
	if(this->posY == this->prevY) {
		this->motionX = this->motionX * 1.1;
		this->motionZ = this->motionZ * 1.1;
	}
	onGround = this->onGround;
	v5 = this->motionX * 0.86;
	this->motionY = this->motionY * 0.86;
	v6 = this->motionZ * 0.86;
	this->motionX = v5;
	this->motionZ = v6;
	if(onGround) {
		this->motionX = v5 * 0.7;
		this->motionZ = v6 * 0.7;
	}
}
void HeartParticle::init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
	float motionY; // s13
	int32_t v9;	   // r2
	float v11;	   // s15

	motionY = this->motionY;
	v9 = a8;
	if(!a8) {
		v9 = 2;
	}
	this->motionX = this->motionX * 0.01;
	this->motionZ = this->motionZ * 0.01;
	this->motionY = (float)(motionY * 0.01) + 0.1;
	v11 = (float)((float)v9 * 0.75) * this->_scale;
	this->_scale = v11;
	this->field_164 = v11;
	this->tick();
}
void HeartParticle::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	float v8; // s15

	v8 = (float)((float)((float)this->ticksAlive + a3) / (float)this->maxAliveTime) * 32.0;
	if(v8 > 1.0) {
		v8 = 1.0;
	} else if(v8 <= 0.0) {
		v8 = 0.0;
	}
	this->_scale = this->field_164 * v8;
	Particle::render(a2, a3, a4, a5, a6, a7, a8);
}
