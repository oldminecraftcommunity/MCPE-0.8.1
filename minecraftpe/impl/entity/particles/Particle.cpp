#include <entity/particles/Particle.hpp>
#include <rendering/Tesselator.hpp>
#include <math/Mth.hpp>
std::string Particle::ITEMS_ATLAS = "items-opaque.png", Particle::TERRAIN_ATLAS = "terrain-atlas.tga", Particle::PARTICLE_ATLAS = "particles.png";
Vec3 Particle::playerViewDir = Vec3::ZERO;
float Particle::zOff, Particle::yOff, Particle::xOff;

Particle::Particle(Level* level, ParticleType a3, const std::string& a4)
	: Entity(level),
	type(a3), textureAtlas(a4), coordMultiplier(0)
{
}
void Particle::_init(float xPos, float yPos, float zPos, float motX, float motY, float motZ, int32_t a8) {
	Entity::_init();
	this->gravity = 0.0f;
	this->field_112 = 1;
	this->ticksAlive = 0;
	this->bColMul = 1.0f;
	this->gColMul = 1.0f;
	this->rColMul = 1.0f;
	this->isDead = 0;
	this->setSize(0.2f, 0.2f);
	this->ridingHeight = this->entityHeight * 0.5f;
	this->setPos(xPos, yPos, zPos);
	this->motionX = motX + (float)((float)(Mth::random()*2 - 1.0f) * 0.4f);
	this->motionY = motY + (float)((float)(Mth::random()*2 - 1.0f) * 0.4f);
	this->motionZ = motZ + (float)((float)(Mth::random()*2 - 1.0f) * 0.4f);

	float v17 = Mth::random();
	float v18 = Mth::random();
	float v19 = sqrt((this->motionX * this->motionX) + (this->motionY * this->motionY) + (this->motionZ * this->motionZ));
	float v20 = (((v17+v18) + 1.0f) * 0.15f * 0.4f) / v19;

	this->motionX *= v20;
	this->motionY = v20 * this->motionY + 0.1f;
	this->motionZ *= v20;
	this->field_138 = Entity::sharedRandom.nextFloat() * 3.0f;
	this->field_13C = Entity::sharedRandom.nextFloat() * 3.0f;
	this->_scale = ((Entity::sharedRandom.nextFloat() * 0.5f) + 0.5f) * 2;
	this->maxAliveTime = (int)(4.0f / ((Entity::sharedRandom.nextFloat() * 0.9f) + 0.1f));
	this->field_110 = 0;
	this->init(xPos, yPos, zPos, motX, motY, motZ, a8);
	this->tick();
}
void Particle::scale(float a2) {
	this->setSize(a2 * 0.2f, a2 * 0.2f);
	this->_scale *= a2;
}
Particle* Particle::setPower(float a2) {
	this->motionX = this->motionX * a2;
	this->motionY = (this->motionY - 0.1f) * a2 + 0.1f;
	this->motionZ = this->motionZ * a2;
	return this;
}

void Particle::tick() {
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;

	this->ticksAlive += 1;
	if(this->ticksAlive >= this->maxAliveTime) {
		this->remove();
	}

	this->motionY -= this->gravity * 0.04f;
	this->move(this->motionX, this->motionY, this->motionZ);

	this->motionX *= 0.98f;
	this->motionY *= 0.98f;
	this->motionZ *= 0.98f;
	if(this->onGround) {
		this->motionX *= 0.7f;
		this->motionZ *= 0.7f;
	}
}

void Particle::render(Tesselator& a2, float pt, float a4, float a5, float a6, float a7, float a8) {
	float minX;			   // r7
	float maxX;			   // r9
	float v2;			   // r8
	float v1;			   // r6
	float v15;			   // s16
	float coordMultiplier; // s14
	float v17;			   // s19
	float v18;			   // s20
	float v19;			   // s18
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
	v15 = this->_scale * 0.1f;
	coordMultiplier = this->coordMultiplier;
	v17 = (this->prevX + (this->posX - this->prevX) * pt) - Particle::xOff + coordMultiplier * Particle::playerViewDir.x;
	v18 = (this->prevY + (this->posY - this->prevY) * pt) - Particle::yOff + coordMultiplier * Particle::playerViewDir.y;
	v19 = (this->prevZ + (this->posZ - this->prevZ) * pt) - Particle::zOff + coordMultiplier * Particle::playerViewDir.z;
	float brightness = this->getBrightness(pt);
	a2.color(brightness * this->rColMul, brightness * this->gColMul, brightness * this->bColMul);
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
