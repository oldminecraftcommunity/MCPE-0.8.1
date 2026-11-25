#include <entity/particles/Particle.hpp>
#include <rendering/Tesselator.hpp>
#include <math/Mth.hpp>

float Particle::xOff, Particle::yOff, Particle::zOff;
Vec3 Particle::playerViewDir = Vec3::ZERO;
std::string
	Particle::PARTICLE_ATLAS = "particles.png",
	Particle::TERRAIN_ATLAS = "terrain-atlas.tga",
	Particle::ITEMS_ATLAS = "items-opaque.png";

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
Particle* Particle::setPower(float a2) {
	this->motionX = this->motionX * a2;
	this->motionY = (this->motionY - 0.1f) * a2 + 0.1f;
	this->motionZ = this->motionZ * a2;
	return this;
}
void Particle::scale(float a2) {
	this->setSize(a2 * 0.2f, a2 * 0.2f);
	this->_scale *= a2;
}

void Particle::tick() {
	int maxAliveTime = this->maxAliveTime;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;
	int ticksAlive = this->ticksAlive;
	this->ticksAlive += 1;
	if(ticksAlive >= maxAliveTime) {
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
	float texMinX = this->texture.minX;
	float texMaxX = this->texture.maxX;
	float texMinY = this->texture.minY;
	float texMaxY = this->texture.maxY;
	float scale = this->_scale * 0.1f;
	float x = (this->prevX + (this->posX - this->prevX) * pt) - Particle::xOff + Particle::playerViewDir.x*this->coordMultiplier;
	float y = (this->prevY + (this->posY - this->prevY) * pt) - Particle::yOff + Particle::playerViewDir.y*this->coordMultiplier;
	float z = (this->prevZ + (this->posZ - this->prevZ) * pt) - Particle::zOff + Particle::playerViewDir.z*this->coordMultiplier;
	float b = this->getBrightness(pt);
	a2.color(b * this->rColMul, b * this->gColMul, b * this->bColMul);


	//<dir> offset <texture dir> texture scaled
	//no idea how else to name it
	//probably something related to rotation?
	//(based on ParticleEngine::render using cos/sin stuff)
	float xoxts = a4 * scale;
	float xoyts = a7 * scale;
	float zoxts = a6 * scale;
	float yoyts = a5 * scale;
	float zoyts = a8 * scale;

	a2.vertexUV((x - xoxts) - xoyts, y - yoyts, (z - zoxts) - zoyts, texMaxX, texMaxY);
	a2.vertexUV((x - xoxts) + xoyts, y + yoyts, (z - zoxts) + zoyts, texMaxX, texMinY);
	a2.vertexUV((x + xoxts) + xoyts, y + yoyts, (z + zoxts) + zoyts, texMinX, texMinY);
	a2.vertexUV((x + xoxts) - xoyts, y - yoyts, (z + zoxts) - zoyts, texMinX, texMaxY);
}
