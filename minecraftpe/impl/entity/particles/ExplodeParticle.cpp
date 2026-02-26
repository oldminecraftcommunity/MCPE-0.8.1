#include <entity/particles/ExplodeParticle.hpp>
#include <math/Mth.hpp>
ExplodeParticle::ExplodeParticle(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->noclip = 0;
}

ExplodeParticle::~ExplodeParticle() {
}
void ExplodeParticle::tick() {
	int32_t maxAliveTime; // r2
	int32_t ticksAlive;	  // r3
	float v4;			  // s15
	float motionX;		  // r1
	bool_t onGround;	  // r3
	float v8;			  // s13
	float v9;			  // s15

	maxAliveTime = this->maxAliveTime;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;
	ticksAlive = this->ticksAlive;
	this->ticksAlive = ticksAlive + 1;
	if(ticksAlive >= maxAliveTime) {
		this->remove();
	}
	this->texture = TextureUVCoordinateSet::fromOldSystem(-8 * this->ticksAlive / this->maxAliveTime + 7);
	v4 = this->motionY + 0.004;
	motionX = this->motionX;
	this->motionY = v4;
	this->move(motionX, v4, this->motionZ);
	onGround = this->onGround;
	v8 = this->motionX * 0.9;
	this->motionY = this->motionY * 0.9;
	v9 = this->motionZ * 0.9;
	this->motionX = v8;
	this->motionZ = v9;
	if(onGround) {
		this->motionX = v8 * 0.7;
		this->motionZ = v9 * 0.7;
	}
}
void ExplodeParticle::init(float xPos, float yPos, float zPos, float motX, float motY, float motZ, int32_t a8) {
	float v9;  // r0
	float v10; // r0
	float v11; // r0
	float v12; // s15
	float f;   // s17

	v9 = Mth::random();
	this->motionX = motX + (float)((float)((float)(v9 + v9) - 1.0) * 0.05);
	v10 = Mth::random();
	this->motionY = motY + (float)((float)((float)(v10 + v10) - 1.0) * 0.05);
	v11 = Mth::random();
	this->motionZ = motZ + (float)((float)((float)(v11 + v11) - 1.0) * 0.05);
	v12 = (float)(Entity::sharedRandom.nextFloat() * 0.3) + 0.7;
	this->bColMul = v12;
	this->gColMul = v12;
	this->rColMul = v12;
	f = Entity::sharedRandom.nextFloat();
	this->_scale = (float)((float)(f * Entity::sharedRandom.nextFloat()) * 6.0) + 1.0;
	this->maxAliveTime = (int32_t)(float)(16.0 / (float)((float)(Entity::sharedRandom.nextFloat() * 0.8) + 0.2)) + 2;
}
