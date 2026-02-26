#include <entity/particles/BreakingItemParticle.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>
#include <rendering/Tesselator.hpp>
BreakingItemParticle::BreakingItemParticle(Level* level, ParticleType pt, const std::string& a2, Item* it)
	: Particle(level, pt, a2) {
	this->item = it;
}

BreakingItemParticle::~BreakingItemParticle() {
}
void BreakingItemParticle::init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
	float v17; // s15

	this->item = Item::items[a8];
	this->texture = *this->item->getIcon(0, 0, 0);
	v17 = this->_scale * 0.5;
	this->bColMul = 1.0;
	this->gColMul = 1.0;
	this->rColMul = 1.0;
	this->_scale = v17;
	this->gravity = Tile::snow->field_3C;
}
void BreakingItemParticle::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	float maxX; // s19
	float maxY; // s18
	float v13;	// s28
	float v14;	// s21
	float v15;	// s16
	float v16;	// s25
	float v17;	// s30
	float v18;	// s23
	float v19;	// r0
	float v20;	// s24
	float v21;	// s17
	float v22;	// s22
	float v23;	// s29
	float v24;	// s16
	float v25;	// s20
	float v26;	// s29
	float v27;	// s24
	float v28;	// s22

	maxX = this->texture.maxX;
	maxY = this->texture.maxY;
	v13 = this->texture.minX + (float)((float)(this->field_138 * 0.25) * (float)(maxX - this->texture.minX));
	v14 = this->texture.minY + (float)((float)(this->field_13C * 0.25) * (float)(maxY - this->texture.minY));
	v15 = this->_scale * 0.1;
	v16 = (float)(this->prevX + (float)((float)(this->posX - this->prevX) * a3)) - Particle::xOff;
	v17 = (float)(this->prevY + (float)((float)(this->posY - this->prevY) * a3)) - Particle::yOff;
	v18 = (float)(this->prevZ + (float)((float)(this->posZ - this->prevZ) * a3)) - Particle::zOff;
	v19 = this->getBrightness(a3);
	a2.color(v19 * this->rColMul, v19 * this->gColMul, v19 * this->bColMul);
	v20 = a4 * v15;
	v21 = a7 * v15;
	v22 = a6 * v15;
	v23 = a5 * v15;
	v24 = a8 * v15;
	v25 = v17 - v23;
	a2.vertexUV((float)(v16 - v20) - v21, v17 - v23, (float)(v18 - v22) - v24, v13, maxY);
	v26 = v17 + v23;
	a2.vertexUV((float)(v16 - v20) + v21, v26, (float)(v18 - v22) + v24, v13, v14);
	v27 = v16 + v20;
	v28 = v18 + v22;
	a2.vertexUV(v27 + v21, v26, v28 + v24, maxX, v14);
	a2.vertexUV(v27 - v21, v25, v28 - v24, maxX, maxY);
}
