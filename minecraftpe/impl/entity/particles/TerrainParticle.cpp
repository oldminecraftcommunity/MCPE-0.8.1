#include <entity/particles/TerrainParticle.hpp>
#include <level/Level.hpp>
#include <rendering/Tesselator.hpp>
#include <tile/Tile.hpp>
TerrainParticle::TerrainParticle(Level* level, ParticleType pt, const std::string& a2)
	: Particle(level, pt, a2) {
	this->rColMul = this->gColMul = this->bColMul = 0.6;
}
TerrainParticle::~TerrainParticle() {
}
void TerrainParticle::init(float a2, float a3, float a4, float a5, float a6, float a7, int32_t a8) {
	Tile* v13;	   // r0
	float v19;	   // s15
	Tile* tile;	   // r0
	int v21;	   // r0
	float gColMul; // s13

	v13 = Tile::tiles[/*(unsigned __int16)a8*/ a8 & 0xffff];
	this->tile = v13;
	this->field_168 = *v13->getTexture(2, /*HIWORD(a8)*/ (a8 >> 16)); //TODO check
	v19 = this->_scale * 0.5;
	tile = this->tile;
	this->gravity = tile->field_3C;
	this->_scale = v19;
	if(tile != Tile::grass) {
		v21 = tile->getColor(this->level, (int32_t)a2, (int32_t)a3, (int32_t)a4);
		gColMul = this->gColMul;
		this->rColMul = this->rColMul * (float)((float)((v21 >> 16) & 0xff) / 255.0);
		this->gColMul = gColMul * (float)((float)((v21 >> 8) & 0xff) / 255.0);
		this->bColMul = this->bColMul * (float)((float)(v21 & 0xff) / 255.0);
	}
}
void TerrainParticle::render(Tesselator& a2, float a3, float a4, float a5, float a6, float a7, float a8) {
	float minX; // s21
	float minY; // s20
	float v13;	// s14
	float v14;	// s19
	float v15;	// s21
	float v16;	// s14
	float v17;	// s18
	float v18;	// s20
	float v19;	// s16
	float v20;	// s26
	float v21;	// s30
	float v22;	// s24
	float v23;	// r0
	float v24;	// s25
	float v25;	// s17
	float v26;	// s23
	float v27;	// s29
	float v28;	// s16
	float v29;	// s22
	float v30;	// s29
	float v31;	// s25
	float v32;	// s23

	minX = this->field_168.minX;
	minY = this->field_168.minY;
	v13 = this->field_168.maxX - minX;
	v14 = minX + (float)((float)(this->field_138 * 0.25) * v13);
	if(v14 != 0.0) {
		minX = this->field_168.minX + (float)((float)(this->field_138 * 0.25) * v13);
	}
	v15 = minX + (float)(v13 * 0.015625);
	v16 = this->field_168.maxY - minY;
	v17 = minY + (float)((float)(this->field_13C * 0.25) * v16);
	if(v17 != 0.0) {
		minY = minY + (float)((float)(this->field_13C * 0.25) * v16);
	}
	v18 = minY + (float)(v16 * 0.015609);
	v19 = this->_scale * 0.1;
	v20 = (float)(this->prevX + (float)((float)(this->posX - this->prevX) * a3)) - Particle::xOff;
	v21 = (float)(this->prevY + (float)((float)(this->posY - this->prevY) * a3)) - Particle::yOff;
	v22 = (float)(this->prevZ + (float)((float)(this->posZ - this->prevZ) * a3)) - Particle::zOff;
	v23 = this->getBrightness(a3);
	a2.color(v23 * this->rColMul, v23 * this->gColMul, v23 * this->bColMul);
	v24 = a4 * v19;
	v25 = a7 * v19;
	v26 = a6 * v19;
	v27 = a5 * v19;
	v28 = a8 * v19;
	v29 = v21 - v27;
	a2.vertexUV((float)(v20 - v24) - v25, v21 - v27, (float)(v22 - v26) - v28, v14, v18);
	v30 = v21 + v27;
	a2.vertexUV((float)(v20 - v24) + v25, v30, (float)(v22 - v26) + v28, v14, v17);
	v31 = v20 + v24;
	v32 = v22 + v26;
	a2.vertexUV(v31 + v25, v30, v32 + v28, v15, v17);
	a2.vertexUV(v31 - v25, v29, v32 - v28, v15, v18);
}
