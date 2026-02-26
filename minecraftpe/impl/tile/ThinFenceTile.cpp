#include <tile/ThinFenceTile.hpp>
#include <level/Level.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


ThinFenceTile::ThinFenceTile(int32_t a2, const std::string& a3, const std::string& a4, const struct Material* a5, bool_t a6)
	: Tile(a2, a3, a5) {
	this->field_98 = a6;
	this->field_80 = *this->getTextureItem(a4)->getUV(0);
}
bool_t ThinFenceTile::attachsTo(int32_t a2) {
	return Tile::solid[a2] || a2 == this->blockID || a2 == Tile::glass->blockID;
}

ThinFenceTile::~ThinFenceTile() {
}
bool_t ThinFenceTile::isCubeShaped() {
	return 0;
}
int32_t ThinFenceTile::getRenderShape() {
	return 18;
}
void ThinFenceTile::updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t v9;	 // r0
	bool_t v10;	 // r10
	int32_t v11; // r0
	bool_t v12;	 // r6
	int32_t v13; // r0
	bool_t v14;	 // r11
	int32_t v15; // r0
	bool_t v16;	 // r0
	float v17;	 // s13
	float v18;	 // r1
	float v19;	 // r3
	float v20;	 // s15

	v9 = level->getTile(x, y, z - 1);
	v10 = this->attachsTo(v9);
	v11 = level->getTile(x, y, z + 1);
	v12 = this->attachsTo(v11);
	v13 = level->getTile(x - 1, y, z);
	v14 = this->attachsTo(v13);
	v15 = level->getTile(x + 1, y, z);
	v16 = this->attachsTo(v15);
	if(v14) {
		v17 = 0.5625;
		v18 = 0.0;
		if(v16) {
			v17 = 1.0;
		}
LABEL_10:
		if(!v10) {
			goto LABEL_14;
		}
		goto LABEL_13;
	}
	if(v16) {
		v17 = 1.0;
		v18 = 0.4375;
		goto LABEL_10;
	}
	if(!v10) {
		if(!v12) {
			v18 = 0.0;
			v17 = 1.0;
			v19 = 0.0;
			v20 = 1.0;
			goto LABEL_29;
		}
		v17 = 0.5625;
		v18 = 0.4375;
LABEL_20:
		v20 = 1.0;
LABEL_27:
		v19 = 0.4375;
		goto LABEL_29;
	}
	v17 = 0.5625;
	v18 = 0.4375;
LABEL_13:
	if(v12) {
LABEL_28:
		v20 = 1.0;
		v19 = 0.0;
		goto LABEL_29;
	}
LABEL_14:
	if(!v14 && !v16) {
		if(!v10) {
			if(!v12) {
				goto LABEL_28;
			}
			goto LABEL_20;
		}
		goto LABEL_22;
	}
	if(!v10) {
		if(!v12) {
			v20 = 0.5625;
			goto LABEL_27;
		}
		goto LABEL_20;
	}
LABEL_22:
	v20 = 0.5625;
	if(v12) {
		v19 = 0.4375;
	} else {
		v19 = 0.0;
	}
LABEL_29:
	this->setShape(v18, 0.0, v19, v17, 1.0, v20);
}
void ThinFenceTile::updateDefaultShape() {
	this->setShape(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
}
bool_t ThinFenceTile::shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t face) {
	return level->getTile(x, y, z) != this->blockID && Tile::shouldRenderFace(level, x, y, z, face);
}
void ThinFenceTile::addAABBs(Level* level, int32_t x, int32_t y, int32_t z, const AABB* a6, std::vector<AABB>& a7) {
	int32_t v11;			// r0
	int32_t v12;			// r0
	bool_t v13;			// r11
	int32_t v14;			// r0
	int32_t v15;			// r0
	bool_t v16;			// r0
	float v18;			// r1
	float v22;			// r3
	float a5;			// [sp+0h] [bp-48h]
	float aaa;			// [sp+8h] [bp-40h]
	bool_t v25;			// [sp+14h] [bp-34h]
	bool_t v26;			// [sp+18h] [bp-30h]
	bool_t v27;			// [sp+1Ch] [bp-2Ch]

	v11 = level->getTile(x, y, z - 1);
	v25 = this->attachsTo(v11);
	v12 = level->getTile(x, y, z + 1);
	v13 = this->attachsTo(v12);
	v14 = level->getTile(x - 1, y, z);
	v27 = this->attachsTo(v14);
	v15 = level->getTile(x + 1, y, z);
	v16 = this->attachsTo(v15);
	v26 = v16;
	if(v27) {
		if(!v16) {
			a5 = 0.5;
LABEL_8:
			v18 = 0.0;
			goto LABEL_10;
		}
LABEL_7:
		a5 = 1.0;
		goto LABEL_8;
	}
	if(!v16) {
		if(v25) {
			goto LABEL_11;
		}
		if(v13) {
			goto LABEL_22;
		}
		goto LABEL_7;
	}
	a5 = 1.0;
	v18 = 0.5;
LABEL_10:
	this->setShape(v18, 0.0, 0.4375, a5, 1.0, 0.5625);
	Tile::addAABBs(level, x, y, z, a6, a7);
	if(!v25) {
LABEL_12:
		if(v27 || v26) {
			if(!v25) {
				if(!v13) {
					return;
				}
				goto LABEL_22;
			}
		} else if(!v25) {
			if(!v13) {
				goto LABEL_16;
			}
LABEL_22:
			aaa = 1.0;
			v22 = 0.5;
			goto LABEL_23;
		}
		if(v13) {
			return;
		}
		aaa = 0.5;
		goto LABEL_20;
	}
LABEL_11:
	if(!v13) {
		goto LABEL_12;
	}
LABEL_16:
	aaa = 1.0;
LABEL_20:
	v22 = 0.0;
LABEL_23:
	this->setShape(0.4375, 0.0, v22, 0.5625, 1.0, aaa);
	Tile::addAABBs(level, x, y, z, a6, a7);
}
bool_t ThinFenceTile::isSolidRender() {
	return 0;
}
int32_t ThinFenceTile::getResource(int32_t a2, Random* a3) {
	if(this->field_98) return Tile::getResource(a2, a3);
	return 0;
}
int32_t ThinFenceTile::getRenderLayer() {
	return 1;
}
