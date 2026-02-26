#include <entity/particles/MobFlameParticle.hpp>
#include <math.h>
std::string MobFlameParticle::FLAME_ATLAS = "fire_atlas.png";

MobFlameParticle::MobFlameParticle(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->noclip = 1;
	this->bColMul = this->gColMul = this->rColMul = 0;
	this->xOff = this->yOff = this->zOff = 0;
	this->texture = {0, 0, 1, 0.03125, 16, 512};
	this->coordMultiplier = -0.25;
}

MobFlameParticle::~MobFlameParticle() {
}
void MobFlameParticle::tick() {
	int32_t ticksAlive;	  // r3
	int32_t maxAliveTime; // r2
	float v4;		  // s15
	float v5;		  // s14
	float posZ;		  // r3
	Entity* entity;	  // r0
	Entity* v8;		  // r0
	Entity* v10;	  // r3
	float xOff;		  // s14
	float v12;		  // s15
	float yOff;		  // s14
	float v14;		  // s15
	float zOff;		  // s14

	ticksAlive = this->ticksAlive;
	maxAliveTime = this->maxAliveTime;
	this->ticksAlive = ticksAlive + 1;
	if(ticksAlive >= maxAliveTime) {
		this->remove();
	} else {
		v4 = this->field_178;
		v5 = this->yOff + v4;
		this->prevX = this->posX;
		this->prevY = this->posY;
		posZ = this->posZ;
		this->yOff = v5;
		this->prevZ = posZ;
		entity = this->entity;
		if(entity) {
			if((float)entity->fire < 2.0 || !entity->isAlive() || (v8 = this->entity, v8->isDead)) {
				this->entity = 0;
			} else if(v8->isOnFire()) {
				v10 = this->entity;
				xOff = this->xOff;
				this->field_178 = this->field_178 + (float)(v10->entityHeight * 0.002);
				v12 = xOff + v10->posX;
				yOff = this->yOff;
				this->posX = v12;
				v14 = yOff + v10->posY;
				zOff = this->zOff;
				this->posY = v14;
				this->posZ = zOff + v10->posZ;
			} else {
				this->entity = 0;
				this->remove();
			}
		} else {
			this->field_178 = v4 + 0.002;
		}
	}
}
float MobFlameParticle::getBrightness(float) {
	return 1;
}
void MobFlameParticle::init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
	float v8; // s15
	float motionY; // s10
	float motionX; // s9
	float scale; // s14

	v8 = a7 + (float)(this->motionZ * 0.1);
	motionY = this->motionY;
	motionX = this->motionX;
	this->entity = 0;
	this->maxAliveTime = 25;
	this->motionZ = v8;
	scale = this->_scale;
	this->motionX = a5 + (float)(motionX * 0.1);
	this->motionY = a6 + (float)(motionY * 0.1);
	this->_scale = scale * 3.0;
	this->field_164 = scale * 3.0;
}
void MobFlameParticle::setEntity(Entity* a2) {
	float posX;		   // s16
	float entityWidth; // s21
	float v6;		   // s16
	float f;		   // r0
	float v8;		   // s21
	float v9;		   // s16
	float v10;		   // s17
	float v11;		   // s21
	float f2;		   // r0
	float v13;		   // s14

	this->entity = a2;
	posX = this->posX;
	this->posY = this->posY + 0.7;
	entityWidth = a2->entityWidth;
	v6 = posX - a2->posX;
	f = Entity::sharedRandom.nextFloat();
	v8 = entityWidth * 0.5;
	v9 = (float)(v6 * v8) + (float)((float)((float)(f + f) - 1.0) * 0.1);
	v10 = this->posY - a2->posY;
	v11 = (float)(this->posZ - a2->posZ) * v8;
	f2 = Entity::sharedRandom.nextFloat();
	v13 = v11 + (float)((float)((float)(f2 + f2) - 1.0) * 0.1);
	if(v9 == 0.0) {
		v9 = 0.0;
	}
	if(v10 == 0.0) {
		v10 = 0.0;
	}
	if(v13 == 0.0) {
		v13 = 0.0;
	}
	this->xOff = v9;
	this->yOff = v10;
	this->zOff = v13;
	this->posX = v9 + a2->posX;
	this->posY = v10 + a2->posY;
	this->posZ = v13 + a2->posZ;
	this->field_178 = (float)(a2->entityHeight * 0.5) * 0.01;
	this->tick();
}
void MobFlameParticle::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	float v12; // s13

	v12 = floorf((float)((float)((float)this->ticksAlive + a3) / (float)this->maxAliveTime) * 32.0);
	this->texture.minY = v12 * 0.03125;
	this->texture.maxY = (float)(v12 * 0.03125) + 0.03125;
	Particle::render(a2, a3, a4, a5, a6, a7, a8);
}
