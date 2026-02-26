#include <tile/GrassTile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

GrassTile::GrassTile(int32_t id)
	: Tile(id, Material::dirt) {
	this->setTicking(1);
	TextureAtlasTextureItem texIt = *this->getTextureItem("grass");
	this->field_98 = *texIt.getUV(0);
	this->field_B0 = *texIt.getUV(1);
	this->field_C8 = *texIt.getUV(2);
	this->field_E0 = *texIt.getUV(3);
	this->field_80 = this->getTextureUVCoordinateSet("dirt", 0);
	this->field_5C = 3;
}
bool_t GrassTile::_randomWalk(Level* level, int32_t& x, int32_t& y, int32_t& z, int32_t a6) {
	Random* p_random; // r5
	int32_t i;		  // r10
	int32_t v11;	  // r3
	uint32_t v13;	  // [sp+0h] [bp-30h]

	p_random = &level->random;
	for(i = 0;; ++i) {
		if(i >= a6 / 16) {
			return a6 > 15;
		}
		x += p_random->genrand_int32() % 3 - 1;
		v13 = p_random->genrand_int32() % 3 - 1;
		y += (int)(p_random->genrand_int32() % 3 * v13) / 2;
		v11 = p_random->genrand_int32() % 3 - 1 + z;
		z = v11;
		if(level->getTile(x, y - 1, v11) != Tile::grass->blockID || level->isSolidBlockingTile(x, y, z)) {
			break;
		}
	}
	return 0;
}

GrassTile::~GrassTile() {
}
bool_t GrassTile::onFertilized(Level* level, int32_t x, int32_t y, int32_t z) {
	Random* p_random; // r10
	int32_t i;		  // r6
	int32_t v10;	  // r8
	int32_t v11;	  // r0
	Tile* v12;		  // r5
	int32_t v15;	  // [sp+1Ch] [bp-34h] BYREF
	int32_t v16;	  // [sp+20h] [bp-30h] BYREF
	int32_t v17;	  // [sp+24h] [bp-2Ch] OVERLAPPED BYREF

	p_random = &level->random;
	for(i = 16; i != 64; ++i) {
		v15 = x;
		v16 = y + 1;
		v17 = z;
		if(this->_randomWalk(level, v15, v16, v17, i)) {
			v10 = level->getTile(v15, v16, v17);
			if(!v10) {
				v11 = p_random->genrand_int32() & 0xF;
				if(v11) {
					if(v11 == 1) {
						v12 = Tile::rose;
						goto LABEL_11;
					}
					v12 = Tile::tallgrass;
					if(v11 != 2) {
						v10 = 1;
LABEL_11:
						if(v12->canSurvive(level, v15, v16, v17)) {
							level->setTileAndData(v15, v16, v17, v12->blockID, v10, 3);
						}
						continue;
					}
				} else {
					v12 = Tile::flower;
				}
				v10 = v11;
				goto LABEL_11;
			}
		}
	}
	return 1;
}
TextureUVCoordinateSet* GrassTile::getTexture(int32_t a2, int32_t a3) {
	if(a2 == 1) {
		return &this->field_98;
	}
	if(a2) {
		return &this->field_B0;
	}
	return &this->field_80;
}
TextureUVCoordinateSet* GrassTile::getTexture(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	Material* v8; // r0

	if(a6 == 1) {
		return &this->field_98;
	}
	if(!a6) {
		return &this->field_80;
	}
	v8 = level->getMaterial(x, y + 1, z);
	if(v8 == Material::topSnow || v8 == Material::snow) {
		return &this->field_C8;
	} else {
		return &this->field_B0;
	}
}
TextureUVCoordinateSet* GrassTile::getCarriedTexture(int32_t a2, int32_t a3) {
	if(a2 == 1) {
		return &this->field_E0;
	} else {
		return this->getTexture(a2, a3);
	}
}
void GrassTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
	int32_t zr;	   // r6
	Material* v10; // r0
	int32_t xr;	   // r5
	int32_t yr;	   // r9
	int32_t v13;   // r10
	int32_t v14;   // r9
	Material* v15; // r0
	Level* v16;	   // r0
	int32_t v17;   // r1
	int32_t v18;   // r2
	int32_t za;	   // [sp+20h] [bp+0h]

	zr = z;
	if(!level->isClientMaybe) {
		if(level->getRawBrightness(x, y + 1, z) <= 3) {
			v10 = level->getMaterial(x, y + 1, z);
			if(v10->blocksLight()) {
				if(random->genrand_int32() << 30) {
					return;
				}
				v16 = level;
				v17 = x;
				v18 = y;
				za = Tile::dirt->blockID;
				goto LABEL_13;
			}
		}
		if(level->getRawBrightness(x, y + 1, z) > 8) {
			xr = x + random->genrand_int32() % 3 - 1;
			yr = y + random->genrand_int32() % 5;
			v13 = yr - 3;
			zr = z + random->genrand_int32() % 3 - 1;
			if(level->getTile(xr, yr - 3, zr) == Tile::dirt->blockID) {
				v14 = yr - 2;
				if(level->getRawBrightness(xr, v14, zr) > 3) {
					v15 = level->getMaterial(xr, v14, zr);
					if(!v15->blocksLight()) {
						v16 = level;
						v17 = xr;
						v18 = v13;
						za = Tile::grass->blockID;
LABEL_13:
						v16->setTile(v17, v18, zr, za, 2);
					}
				}
			}
		}
	}
}
int32_t GrassTile::getResource(int32_t, Random* a3) {
	return Tile::dirt->getResource(0, a3);
}
int32_t GrassTile::getColor(int32_t) {
	return 0x87CD49;
}
int32_t GrassTile::getColor(LevelSource*, int32_t, int32_t, int32_t) {
	return this->getColor(0);
}
