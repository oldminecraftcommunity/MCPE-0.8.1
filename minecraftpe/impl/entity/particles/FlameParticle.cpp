#include <entity/particles/FlameParticle.hpp>
#include <math/Mth.hpp>
FlameParticle::FlameParticle(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->noclip = 1;
	this->texture = {0, 0.1875, 0.0625, 0.25, 256, 256};
}

FlameParticle::~FlameParticle() {
}
void FlameParticle::tick() {
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
	onGround = this->onGround;
	v5 = this->motionX * 0.96;
	this->motionY = this->motionY * 0.96;
	v6 = this->motionZ * 0.96;
	this->motionX = v5;
	this->motionZ = v6;
	if(onGround) {
		this->motionX = v5 * 0.7;
		this->motionZ = v6 * 0.7;
	}
}
float FlameParticle::getBrightness(float) {
	return 1.0;
}
void FlameParticle::init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
	this->motionX = a5 + (float)(this->motionX * 0.01);
	this->motionY = a6 + (float)(this->motionY * 0.01);
	this->motionZ = a7 + (float)(this->motionZ * 0.01);
	Entity::sharedRandom.nextFloat();
	Entity::sharedRandom.nextFloat();
	Entity::sharedRandom.nextFloat();
	Entity::sharedRandom.nextFloat();
	Entity::sharedRandom.nextFloat();
	Entity::sharedRandom.nextFloat();
	this->field_164 = this->_scale;
	this->bColMul = 1.0;
	this->gColMul = 1.0;
	this->rColMul = 1.0;
	this->maxAliveTime = (int32_t)(float)(8.0 / (float)((float)(Mth::random() * 0.8) + 0.2)) + 4;
}
void FlameParticle::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	float v8; // s15

	v8 = (float)((float)this->ticksAlive + a3) / (float)this->maxAliveTime;
	this->_scale = this->field_164 * (float)(1.0 - (float)((float)(v8 * v8) * 0.5));
	Particle::render(a2, a3, a4, a5, a6, a7, a8);
}
