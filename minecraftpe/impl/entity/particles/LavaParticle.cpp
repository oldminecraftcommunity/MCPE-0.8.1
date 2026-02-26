#include <entity/particles/LavaParticle.hpp>
#include <math/Mth.hpp>
#include <level/Level.hpp>
LavaParticle::LavaParticle(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->bColMul = this->gColMul = this->rColMul = 1;
	this->noclip = 0;
	this->texture = {0, 0.1875, 0.125, 0.25, 256, 256};
}

LavaParticle::~LavaParticle() {
}
void LavaParticle::tick() {
	int32_t maxAliveTime; // r2
	int32_t ticksAlive;	  // r3
	float v4;		  // s16
	float v5;		  // s15
	float motionX;	  // r1
	bool_t onGround;  // r3
	float v9;		  // s13
	float v10;		  // s15

	maxAliveTime = this->maxAliveTime;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;
	ticksAlive = this->ticksAlive;
	this->ticksAlive = ticksAlive + 1;
	if(ticksAlive >= maxAliveTime) {
		this->remove();
	}
	v4 = (float)this->ticksAlive / (float)this->maxAliveTime;
	if(Entity::sharedRandom.nextFloat() > v4) {
		this->level->addParticle(PT_SMOKE, this->posX, this->posY, this->posZ, this->motionX, this->motionY, this->motionZ, 0);
	}
	v5 = this->motionY - 0.03;
	motionX = this->motionX;
	this->motionY = v5;
	this->move(motionX, v5, this->motionZ);
	onGround = this->onGround;
	v9 = this->motionX * 0.999;
	this->motionY = this->motionY * 0.999;
	v10 = this->motionZ * 0.999;
	this->motionX = v9;
	this->motionZ = v10;
	if(onGround) {
		this->motionX = v9 * 0.7;
		this->motionZ = v10 * 0.7;
	}
}
float LavaParticle::getBrightness(float) {
	return 1.0;
}
void LavaParticle::init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8){
	float f; // r0
	float v10; // s15

	this->motionX = this->motionX * 0.8;
	this->motionY = this->motionY * 0.8;
	this->motionZ = this->motionZ * 0.8;
	this->motionY = (float)(Entity::sharedRandom.nextFloat() * 0.4) + 0.05;
	f = Entity::sharedRandom.nextFloat();
	v10 = (float)((float)(f + f) + 0.2) * this->_scale;
	this->_scale = v10;
	this->scaleMult = v10;
	this->maxAliveTime = (int)(16.0 / (Mth::random() * 0.8 + 0.2));
}
void LavaParticle::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8){
	float v8; // s14

	v8 = (float)((float)this->ticksAlive + a3) / (float)this->maxAliveTime;
	this->_scale = this->scaleMult * (float)(1.0 - (float)(v8 * v8));
	Particle::render(a2, a3, a4, a5, a6, a7, a8);
}
