#include <entity/particles/BubbleParticle.hpp>
#include <math/Mth.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
BubbleParticle::BubbleParticle(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->rColMul = 1;
	this->gColMul = 1;
	this->bColMul = 1;
	this->setSize(0.02, 0.02);
	this->texture = {0, 0.125, 0.0625, 0.1875, 256, 256};
}
BubbleParticle::~BubbleParticle() {
}
void BubbleParticle::tick() {
	float v1;			  // s15
	float motionX;		  // r1
	float posZ;			  // r3
	Level* level;		  // r0
	float posX;			  // s15
	int32_t v8;			  // r1
	bool_t v9;			  // fnf
	float posY;			  // s15
	int32_t v11;		  // r2
	bool_t v12;			  // fnf
	float v13;			  // s15
	int32_t v14;		  // r3
	int32_t maxAliveTime; // r3

	v1 = this->motionY + 0.002;
	motionX = this->motionX;
	this->prevX = this->posX;
	this->prevY = this->posY;
	posZ = this->posZ;
	this->motionY = v1;
	this->prevZ = posZ;
	this->move(motionX, v1, this->motionZ);
	level = this->level;
	this->motionX = this->motionX * 0.85;
	this->motionY = this->motionY * 0.85;
	this->motionZ = this->motionZ * 0.85;
	posX = this->posX;
	v8 = (int32_t)posX;
	v9 = posX < (float)(int32_t)posX;
	posY = this->posY;
	v11 = (int32_t)posY;
	if(v9) {
		--v8;
	}
	v12 = posY < (float)(int32_t)posY;
	v13 = this->posZ;
	v14 = (int32_t)v13;
	if(v12) {
		--v11;
	}
	if(v13 < (float)(int32_t)v13) {
		--v14;
	}
	if(Material::water != level->getMaterial(v8, v11, v14)) {
		this->remove();
	}
	maxAliveTime = this->maxAliveTime;
	this->maxAliveTime = maxAliveTime - 1;
	if(maxAliveTime <= 0) {
		this->remove();
	}
}
void BubbleParticle::init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
	float scale; // s17
	float v10;	 // r0
	float v11;	 // r0
	float v12;	 // r0

	scale = this->_scale;
	this->_scale = scale * (float)((float)(Entity::sharedRandom.nextFloat() * 0.6) + 0.2);
	v10 = Mth::random();
	this->motionX = (float)((float)((float)(v10 + v10) - 1.0) * 0.02) + (float)(a5 * 0.2);
	v11 = Mth::random();
	this->motionY = (float)((float)((float)(v11 + v11) - 1.0) * 0.02) + (float)(a6 * 0.2);
	v12 = Mth::random();
	this->motionZ = (float)((float)((float)(v12 + v12) - 1.0) * 0.02) + (float)(a7 * 0.2);
	this->maxAliveTime = (int)(8.0 / (Mth::random() * 0.8 + 0.2));
}
