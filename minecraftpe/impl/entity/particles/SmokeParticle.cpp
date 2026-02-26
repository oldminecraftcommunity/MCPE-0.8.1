#include <entity/particles/SmokeParticle.hpp>
#include <math/Mth.hpp>
SmokeParticle::SmokeParticle(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->noclip = 0;
}

SmokeParticle::~SmokeParticle() {
}
void SmokeParticle::tick() {
	int32_t maxAliveTime; // r2
	int32_t ticksAlive;	  // r3
	float v4;		  // s15
	float motionX;	  // r1
	bool_t onGround;  // r3
	float v8;		  // s13
	float v9;		  // s15

	maxAliveTime = this->maxAliveTime;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;
	ticksAlive = this->ticksAlive;
	this->ticksAlive = ticksAlive + 1;
	if(ticksAlive >= maxAliveTime) {
		this->remove();
	}
	v4 = this->motionY + 0.004;
	motionX = this->motionX;
	this->motionY = v4;
	this->move(motionX, v4, this->motionZ);
	if(this->posY == this->prevY) {
		this->motionX = this->motionX * 1.1;
		this->motionZ = this->motionZ * 1.1;
	}
	onGround = this->onGround;
	v8 = this->motionX * 0.96;
	this->motionY = this->motionY * 0.96;
	v9 = this->motionZ * 0.96;
	this->motionX = v8;
	this->motionZ = v9;
	if(onGround) {
		this->motionX = v8 * 0.7;
		this->motionZ = v9 * 0.7;
	}
}
void SmokeParticle::init(float xPos, float yPos, float zPos, float motX, float motY, float motZ, int32_t a8){
	float motionY; // s10
	int32_t v9;	   // r3
	float v11;	   // s16
	float v12;	   // s14
	float v13;	   // r0
	float v14;	   // s15

	motionY = this->motionY;
	v9 = a8;
	if(!a8) {
		v9 = 100;
	}
	v11 = (float)v9 / 100.0;
	v12 = motZ + (float)(this->motionZ * 0.1);
	this->motionX = motX + (float)(this->motionX * 0.1);
	this->motionZ = v12;
	this->motionY = motY + (float)(motionY * 0.1);
	v13 = Mth::random();
	this->bColMul = v13 * 0.5;
	this->gColMul = v13 * 0.5;
	this->rColMul = v13 * 0.5;
	v14 = (float)(this->_scale * 0.75) * v11;
	this->_scale = v14;
	this->field_164 = v14;
	this->maxAliveTime = (int32_t)(float)((float)(v11 * 8.0) / (float)((float)(Mth::random() * 0.8) + 0.2));
}
void SmokeParticle::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	float v12; // s16

	v12 = (float)((float)((float)this->ticksAlive + a3) / (float)this->maxAliveTime) * 32.0;
	if(v12 < 0.0) {
		v12 = 0.0;
	} else if(v12 > 1.0) {
		v12 = 1.0;
	}
	this->texture = TextureUVCoordinateSet::fromOldSystem(-8 * this->ticksAlive / this->maxAliveTime + 7);
	this->_scale = this->field_164 * v12;
	Particle::render(a2, a3, a4, a5, a6, a7, a8);
}
