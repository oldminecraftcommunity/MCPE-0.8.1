#include <entity/particles/CritParticle2.hpp>
#include <math/Mth.hpp>
CritParticle2::CritParticle2(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->field_164 = 1;
	this->texture = {0.0625, 0.25, 0.125, 0.3125, 256, 256};
	this->noclip = 0;
}

CritParticle2::~CritParticle2() {
}
void CritParticle2::tick() {
	int32_t maxAliveTime; // r2
	int32_t ticksAlive;	  // r3
	float bColMul;		  // s14
	float motionY;		  // s11
	float motionX;		  // s12
	float motionZ;		  // s13
	bool_t onGround;	  // r3
	float v9;			  // s12
	float v10;			  // s13

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
	bColMul = this->bColMul;
	motionY = this->motionY;
	motionX = this->motionX;
	motionZ = this->motionZ;
	onGround = this->onGround;
	this->gColMul = this->gColMul * 0.96;
	this->bColMul = bColMul * 0.9;
	v9 = motionX * 0.7;
	this->motionY = (float)(motionY * 0.7) - 0.02;
	v10 = motionZ * 0.7;
	this->motionX = v9;
	this->motionZ = v10;
	if(onGround) {
		this->motionX = v9 * 0.7;
		this->motionZ = v10 * 0.7;
	}
}
void CritParticle2::init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
	float motionY; // s11
	float motionZ; // s12
	float v11;	   // s13
	float scale;   // s14
	float v13;	   // s15
	float v14;	   // r0

	motionY = this->motionY;
	motionZ = this->motionZ;
	this->motionX = (float)(a5 * 0.4) + (float)(this->motionX * 0.1);
	this->motionY = (float)(a6 * 0.4) + (float)(motionY * 0.1);
	this->motionZ = (float)(a7 * 0.4) + (float)(motionZ * 0.1);
	v11 = (float)(Mth::random() * 0.3) + 0.6;
	scale = this->_scale;
	this->bColMul = v11;
	this->gColMul = v11;
	this->rColMul = v11;
	v13 = (float)(scale * 0.75) * (float)a8;
	this->_scale = v13;
	this->field_168 = v13;
	v14 = Mth::random();
	this->maxAliveTime = (int32_t)(float)((float)(6.0 / (float)((float)(v14 * 0.8) + 0.6)) * (float)a8);
	this->tick();
}
void CritParticle2::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	float v8; // s15

	if(this->field_164) {
		v8 = (float)((float)((float)this->ticksAlive + a3) / (float)this->maxAliveTime) * 32.0;
		if(v8 < 0.0) {
			v8 = 0.0;
		} else if(v8 > 1.0) {
			v8 = 1.0;
		}
		this->_scale = this->field_168 * v8;
		Particle::render(a2, a3, a4, a5, a6, a7, a8);
	}
}
