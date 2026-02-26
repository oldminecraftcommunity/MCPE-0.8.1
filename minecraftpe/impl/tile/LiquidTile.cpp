#include <tile/LiquidTile.hpp>
#include <tile/material/Material.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Vec3.hpp>
#include <math/Mth.hpp>

LiquidTile::LiquidTile(int32_t id, const Material* mat, const std::string& a4, const std::string& a5)
	: Tile(id, a4, mat) {
	this->field_AC = *this->getTextureItem(a4);
	this->field_7C = this->getTextureUVCoordinateSet(a4, 0);
	this->field_94 = this->getTextureUVCoordinateSet(a5, 0);
	this->replaceable = 1;
}


void LiquidTile::_trySpreadFire(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
	int32_t v7; // r8
	int32_t v8; // r9
	int32_t v9; // r10
	Tile* v10; // r3
	int32_t v12; // [sp+4h] [bp-3Ch]

	if(!level->instantTick) {
		static Vec3 vecs[6] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
		v12 = 10;
		while(1) {
			v7 = x + (random->genrand_int32() & 3) - 2;
			v8 = y + (random->genrand_int32() & 3) - 2;
			v9 = z + (random->genrand_int32() & 3) - 2;
			v10 = Tile::tiles[level->getTile(v7, v8, v9)];
			if(v10) {
				if(v10->material->isFlammable()) {
					break;
				}
			}
LABEL_13:
			if(!--v12) {
				return;
			}
		}

		for(Vec3& v: vecs) {
			if(!level->getTile(v.x + v7, v.y + v8, v.z + v9)) {
				level->setTile(v.x + v7, v.y + v8, v.z + v9, Tile::fire->blockID, 3);
				break;
			}
		}
		goto LABEL_13;
	}
}
void LiquidTile::fizz(Level* level, int32_t x, int32_t y, int32_t z) {
	Random* p_random; // r6
	float v7; // s16
	float v8; // s18
	float f; // s19
	float f1; // r0
	int32_t v11; // r5
	float v12; // s20
	float v13; // r0

	p_random = &level->random;
	v7 = (float)y;
	v8 = (float)x;
	f = p_random->nextFloat();
	f1 = p_random->nextFloat();
	level->playSound(v8 + 0.5, v7 + 0.5, (float)z + 0.5, "random.fizz", 0.5, (float)((float)(f - f1) * 0.8) + 2.6);
	v11 = 8;
	do {
		v12 = v8 + Mth::random();
		v13 = Mth::random();
		level->addParticle(PT_SMOKE, v12, v7 + 1.2, (float)z + v13, 0.0, 0.0, 0.0, 250);
		--v11;
	} while(v11);
}
int32_t LiquidTile::getDepth(Level* level, int32_t x, int32_t y, int32_t z) {
	if(this->material == level->getMaterial(x, y, z)) {
		return level->getData(x, y, z);
	} else {
		return -1;
	}
}
Vec3 LiquidTile::getFlow(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t v10;   // r11
	int32_t v11;   // r10
	int32_t v12;   // r9
	int32_t v13;   // r0
	Material* v14; // r0
	int32_t v15;   // r0
	int32_t v16;   // r0
	float v17;	   // s14
	float v18;	   // s13
	float v19;	   // s15
	int32_t v20;   // r10
	float v21;	   // s14
	float v22;	   // s15
	float v23;	   // s17
	bool_t v24;	   // fzf
	float v25;	   // r1
	float v26;	   // r2
	int32_t depth; // [sp+Ch] [bp-5Ch]
	Vec3 res = {0, 0, 0};
	v10 = 0;
	depth = this->getRenderedDepth(level, x, y, z);
	do {
		if(v10) {
			switch(v10) {
				case 1:
					v12 = z - 1;
					break;
				case 2:
					v11 = x + 1;
					goto LABEL_12;
				case 3:
					v12 = z + 1;
					break;
				default:
					v11 = x;
					goto LABEL_12;
			}
			v11 = x;
			goto LABEL_13;
		}
		v11 = x - 1;
LABEL_12:
		v12 = z;
LABEL_13:
		v13 = this->getRenderedDepth(level, v11, y, v12);
		if(v13 >= 0) {
			v16 = v13 - depth;
			goto LABEL_18;
		}
		v14 = level->getMaterial(v11, y, v12);
		if(!v14->blocksMotion()) {
			v15 = this->getRenderedDepth(level, v11, y - 1, v12);
			if(v15 >= 0) {
				v16 = v15 + 8 - depth;
LABEL_18:
				v17 = res.y + 0.0;
				v18 = (float)(v16 * (v11 - x)) + res.x;
				v19 = (float)(v16 * (v12 - z)) + res.z;
				if(v18 == 0.0) {
					v18 = 0.0;
				}
				res.x = v18;
				if(v17 == 0.0) {
					v17 = 0.0;
				}
				res.y = v17;
				if(v19 == 0.0) {
					v19 = 0.0;
				}
				res.z = v19;
			}
		}
		++v10;
	} while(v10 != 4);
	if(level->getData(x, y, z) > 7) {
		if(this->shouldRenderFace(level, x, y, z - 1, 2) || this->shouldRenderFace(level, x, y, z + 1, 3) || this->shouldRenderFace(level, x - 1, y, z, 4) || this->shouldRenderFace(level, x + 1, y, z, 5) || (v20 = y + 1, this->shouldRenderFace(level, x, y + 1, z - 1, 2)) || this->shouldRenderFace(level, x, v20, z + 1, 3) || this->shouldRenderFace(level, x - 1, v20, z, 4) || this->shouldRenderFace(level, x + 1, v20, z, 5)) {
			Vec3 result = res.normalized();
			v21 = result.x + 0.0;
			v22 = result.y - 6.0;
			v23 = result.z + 0.0;
			v24 = (float)(result.y - 6.0) == 0.0;
			if((float)(result.x + 0.0) == 0.0) {
				v21 = 0.0;
			}
			res.x = v21;
			if(v24) {
				v22 = 0.0;
			}
			res.y = v22;
			if(v23 == 0.0) {
				v23 = 0.0;
			}
			res.z = v23;
		}
	}
	Vec3 v28 = res.normalized();
	res = v28;
	return res;
}
int32_t LiquidTile::getRenderedDepth(struct LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t meta; // r0

	if(this->material != level->getMaterial(x, y, z)) {
		return -1;
	}
	meta = level->getData(x, y, z);
	if(meta > 7) {
		return 0;
	}
	return meta;
}
float LiquidTile::getSlopeAngle(LevelSource* level, int32_t x, int32_t y, int32_t z, const struct Material* m) {
	float v9; // s15
	float v10; // s14

	if(m == Material::water) {
		Vec3 a1 = ((LiquidTile*)Tile::water)->getFlow(level, x, y, z);
		v9 = a1.z;
		v10 = a1.x;
	} else {
		v9 = 0.0;
		v10 = 0.0;
	}
	if(m == Material::lava) {
		Vec3 a1 = ((LiquidTile*)Tile::water)->getFlow(level, x, y, z);
		v9 = a1.z;
		v10 = a1.x;
	}
	if(v10 == 0.0 && v9 == 0.0) {
		return -1000.0;
	} else {
		return atan2(v9, v10) - (float)(3.1416 * 0.5);
	}
}
void LiquidTile::updateLiquid(Level* level, int32_t x, int32_t y, int32_t z) {
	Tile* v9; // r3
	int32_t v10; // r0

	if(level->getTile(x, y, z) == this->blockID && this->material == Material::lava && (Material::water == level->getMaterial(x, y, z - 1) || Material::water == level->getMaterial(x, y, z + 1) || Material::water == level->getMaterial(x - 1, y, z) || Material::water == level->getMaterial(x + 1, y, z) || Material::water == level->getMaterial(x, y + 1, z))) {
		v10 = level->getData(x, y, z);
		if(v10) {
			if(v10 > 4) {
LABEL_12:
				this->fizz(level, x, y, z);
				return;
			}
			v9 = Tile::stoneBrick;
		} else {
			v9 = Tile::obsidian;
		}
		level->setTile(x, y, z, v9->blockID, 3);
		goto LABEL_12;
	}
}

LiquidTile::~LiquidTile() {
}
bool_t LiquidTile::isCubeShaped() {
	return 0;
}
int32_t LiquidTile::getRenderShape() {
	return 4;
}
float LiquidTile::getBrightness(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	float b; // s16
	float bu; // r0

	b = level->getBrightness(x, y, z);
	bu = level->getBrightness(x, y + 1, z);
	if(b > bu) {
		return b;
	}
	return bu;
}
bool_t LiquidTile::shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t face) {
	Material* mat; // r0

	mat = level->getMaterial(x, y, z);
	if(mat == this->material || mat == Material::ice) {
		return 0;
	}
	if(face == 1) {
		return 1;
	}
	return Tile::shouldRenderFace(level, x, y, z, face);
}
TextureUVCoordinateSet* LiquidTile::getTexture(int32_t a2) {
	if((uint32_t)a2 > 1) {
		return &this->field_94;
	} else {
		return &this->field_7C;
	}
}
AABB* LiquidTile::getAABB(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t LiquidTile::isSolidRender() {
	return 0;
}
bool_t LiquidTile::isLiquidTile() {
	return 1;
}
bool_t LiquidTile::mayPick(int32_t a2, bool_t a3) {
	return a3 && a2 == 0;
}
int32_t LiquidTile::getTickDelay() {
	if(this->material == Material::water) return 5;
	if(this->material == Material::lava) return 30;
	return 0;
}
void LiquidTile::tick(Level*, int32_t, int32_t, int32_t, Random*) {
}
void LiquidTile::animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	float f1;	// s17
	float maxY; // s15
	float f;	// r0

	if(this->material == Material::water && !(rng->genrand_int32() << 26)) {
		level->getData(x, y, z);
	}
	if(this->material == Material::lava && Material::air == level->getMaterial(x, y + 1, z) && !level->isSolidRenderTile(x, y + 1, z) && !(rng->genrand_int32() % 0x64)) {
		f1 = (float)x + rng->nextFloat();
		maxY = this->maxY;
		f = rng->nextFloat();
		level->addParticle(PT_LAVA, f1, (float)y + maxY, (float)z + f, 0.0, 0.0, 0.0, 0);
	}
}
void LiquidTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
	this->updateLiquid(level, x, y, z);
}
void LiquidTile::onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	this->updateLiquid(level, x, y, z);
}
int32_t LiquidTile::getResource(int32_t, Random*) {
	return 0;
}
int32_t LiquidTile::getResourceCount(Random*) {
	return 0;
}
int32_t LiquidTile::getRenderLayer() {
	if(this->material == Material::water) return 2;
	return 0;
}
void LiquidTile::handleEntityInside(Level* level, int32_t x, int32_t y, int32_t z, Entity* ent, Vec3& a7) {
	float yy; // s13
	float v8; // s15
	float zz; // s13

	Vec3 a1 = this->getFlow(level, x, y, z);
	yy = a1.y;
	a7.x = a7.x + (float)(a1.x * 0.5);
	v8 = a7.y + (float)(yy * 0.5);
	zz = a1.z;
	a7.y = v8;
	a7.z = a7.z + (float)(zz * 0.5);
}
int32_t LiquidTile::getColor(LevelSource*, int32_t, int32_t, int32_t){
	return 0x999999FF;
}
TextureUVCoordinateSet* LiquidTile::getTextureNum(int32_t a2) {
	return this->field_AC.getUV(a2);
}
