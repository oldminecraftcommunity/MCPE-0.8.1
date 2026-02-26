#include <entity/particles/Particle.hpp>
#include <rendering/Tesselator.hpp>
#include <math/Mth.hpp>
std::string Particle::ITEMS_ATLAS = "items-opaque.png", Particle::TERRAIN_ATLAS = "terrain-atlas.tga", Particle::PARTICLE_ATLAS = "particles.png";
Vec3 Particle::playerViewDir = Vec3::ZERO;
float Particle::zOff, Particle::yOff, Particle::xOff;

Particle::Particle(Level* level, ParticleType a3, const std::string& a4)
	: Entity(level) {
	this->type = a3;
	this->textureAtlas = a4;
	this->coordMultiplier = 0;
	this->texture.minX = 0;
	this->texture.minY = 0;
	this->texture.maxX = 0;
	this->texture.maxY = 0;
}
void Particle::_init(float xPos, float yPos, float zPos, float motX, float motY, float motZ, int32_t a8) {
	float v14;	   // r0
	float v15;	   // r0
	float v16;	   // r0
	float v17;	   // s23
	float v18;	   // s22
	float v19;	   // s15
	float v20;	   // s17
	float motionZ; // s15
	float f;	   // r0
	float Float;   // r0

	Entity::_init();
	this->gravity = 0.0;
	this->field_112 = 1;
	this->ticksAlive = 0;
	this->bColMul = 1.0;
	this->gColMul = 1.0;
	this->rColMul = 1.0;
	this->isDead = 0;
	this->setSize(0.2, 0.2);
	this->ridingHeight = this->entityHeight * 0.5;
	this->setPos(xPos, yPos, zPos);
	v14 = Mth::random();
	this->motionX = motX + (float)((float)((float)(v14 + v14) - 1.0) * 0.4);
	v15 = Mth::random();
	this->motionY = motY + (float)((float)((float)(v15 + v15) - 1.0) * 0.4);
	v16 = Mth::random();
	this->motionZ = motZ + (float)((float)((float)(v16 + v16) - 1.0) * 0.4);
	v17 = Mth::random();
	v18 = Mth::random();
	v19 = sqrt((float)((float)((float)(this->motionY * this->motionY) + (float)(this->motionX * this->motionX)) + (float)(this->motionZ * this->motionZ)));
	v20 = (float)((float)((float)((float)(v17 + v18) + 1.0) * 0.15) * 0.4) / v19;
	this->motionX = this->motionX * v20;
	motionZ = this->motionZ;
	this->motionY = (float)(v20 * this->motionY) + 0.1;
	this->motionZ = motionZ * v20;
	this->field_138 = Entity::sharedRandom.nextFloat() * 3.0;
	this->field_13C = Entity::sharedRandom.nextFloat() * 3.0;
	f = Entity::sharedRandom.nextFloat();
	this->_scale = (float)((float)(f * 0.5) + 0.5) + (float)((float)(f * 0.5) + 0.5);
	Float = Entity::sharedRandom.nextFloat();
	this->field_110 = 0;
	this->maxAliveTime = (int)(float)(4.0 / (float)((float)(Float * 0.9) + 0.1));
	this->init(xPos, yPos, zPos, motX, motY, motZ, a8);
	this->tick();
}
void Particle::scale(float a2) {
	this->setSize(a2 * 0.2, a2 * 0.2);
	this->_scale *= a2;
}
Particle* Particle::setPower(float a2) {
	this->motionX = this->motionX * a2;
	this->motionY = (float)((float)(this->motionY - 0.1) * a2) + 0.1;
	this->motionZ = this->motionZ * a2;
	return this;
}

Particle::~Particle() {
}
void Particle::tick() {
	int32_t maxAliveTime; // r2
	int32_t ticksAlive; // r3
	float v4; // s15
	float motionX; // r1
	bool_t onGround; // r3
	float v8; // s13
	float v9; // s15

	maxAliveTime = this->maxAliveTime;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;
	ticksAlive = this->ticksAlive;
	this->ticksAlive = ticksAlive + 1;
	if(ticksAlive >= maxAliveTime) {
		this->remove();
	}
	v4 = this->motionY - (float)(this->gravity * 0.04);
	motionX = this->motionX;
	this->motionY = v4;
	this->move(motionX, v4, this->motionZ);
	onGround = this->onGround;
	v8 = this->motionX * 0.98;
	this->motionY = this->motionY * 0.98;
	v9 = this->motionZ * 0.98;
	this->motionX = v8;
	this->motionZ = v9;
	if(onGround) {
		this->motionX = v8 * 0.7;
		this->motionZ = v9 * 0.7;
	}
}
int32_t Particle::getEntityTypeId() const {
	return 0;
}
void Particle::readAdditionalSaveData(CompoundTag*) {
}
void Particle::addAdditonalSaveData(CompoundTag*) {
}
void Particle::setEntity(Entity*) {
}
void Particle::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	float minX;			   // r7
	float maxX;			   // r9
	float v2;			   // r8
	float v1;			   // r6
	float v15;			   // s16
	float coordMultiplier; // s14
	float v17;			   // s19
	float v18;			   // s20
	float v19;			   // s18
	float v20;			   // r0
	float v21;			   // s23
	float v22;			   // s17
	float v23;			   // s22
	float v24;			   // s26
	float v25;			   // s16
	float v26;			   // s21
	float v27;			   // s20
	float v28;			   // s19
	float v29;			   // s18

	minX = this->texture.minX;
	maxX = this->texture.maxX;
	v2 = this->texture.minY;
	v1 = this->texture.maxY;
	v15 = this->_scale * 0.1;
	coordMultiplier = this->coordMultiplier;
	v17 = (float)((float)(this->prevX + (float)((float)(this->posX - this->prevX) * a3)) - Particle::xOff) + (float)(coordMultiplier * Particle::playerViewDir.x);
	v18 = (float)((float)(this->prevY + (float)((float)(this->posY - this->prevY) * a3)) - Particle::yOff) + (float)(coordMultiplier * Particle::playerViewDir.y);
	v19 = (float)((float)(this->prevZ + (float)((float)(this->posZ - this->prevZ) * a3)) - Particle::zOff) + (float)(coordMultiplier * Particle::playerViewDir.z);
	v20 = this->getBrightness(a3);
	a2.color(v20 * this->rColMul, v20 * this->gColMul, v20 * this->bColMul);
	v21 = a4 * v15;
	v22 = a7 * v15;
	v23 = a6 * v15;
	v24 = a5 * v15;
	v25 = a8 * v15;
	v26 = v18 - v24;
	a2.vertexUV((float)(v17 - v21) - v22, v18 - v24, (float)(v19 - v23) - v25, maxX, v1);
	v27 = v18 + v24;
	a2.vertexUV((float)(v17 - v21) + v22, v27, (float)(v19 - v23) + v25, maxX, v2);
	v28 = v17 + v21;
	v29 = v19 + v23;
	a2.vertexUV(v28 + v22, v27, v29 + v25, minX, v2);
	a2.vertexUV(v28 - v22, v26, v29 - v25, minX, v1);
}
