#include <level/gen/feature/PineFeature.hpp>
#include <tile/Tile.hpp>
#include <level/Level.hpp>

PineFeature::PineFeature() : Feature(0){

}

PineFeature::~PineFeature() {
}
bool_t PineFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z) {
	int32_t v9;	 // r9
	int8_t v10;	 // r8
	int32_t v11; // r0
	int32_t v13; // r1
	bool_t v14;	 // r8
	int32_t v15; // r7
	int32_t v16; // r0
	int32_t i;	 // r11
	int32_t v18; // r10
	int32_t v19; // r0
	int32_t v20; // r7
	int32_t j;	 // r8
	int32_t v22; // r10
	int32_t a5;	 // r9
	int32_t v24; // r3
	int32_t k;	 // r7
	int32_t v26; // r0
	int32_t v27; // r2
	int32_t v28; // r9
	int32_t a4;	 // [sp+10h] [bp-48h]
	int32_t v30; // [sp+14h] [bp-44h]
	int32_t v31; // [sp+18h] [bp-40h]
	int32_t v33; // [sp+20h] [bp-38h]
	int32_t v34; // [sp+24h] [bp-34h]
	int32_t v35; // [sp+28h] [bp-30h]
	int32_t v36; // [sp+2Ch] [bp-2Ch]

	v31 = random->genrand_int32() % 5;
	v9 = v31 + 7;
	v10 = random->genrand_int32();
	v11 = random->genrand_int32();
	if(y <= 0) {
		return 0;
	}
	a4 = y + v9;
	if(y + v9 > 127) {
		return 0;
	}
	v30 = v9 - (v10 & 1) - 3;
	v13 = (v10 & 1) + 3;
	v14 = 1;
	v15 = y;
	v36 = y + 1 + v9;
	v35 = v11 % (uint32_t)(v13 + 1) + 1;
	while(v15 <= v36) {
		if(!v14) {
			return 0;
		}
		v27 = v35;
		if(v15 - y < v30) {
			v27 = 0;
		}
		v18 = x - v27;
		v28 = v27;
		v33 = x + v27;
		v34 = z + v27;
		while(v18 <= v33 && v14) {
			for(i = z - v28; i <= v34 && v14; ++i) {
				if((uint32_t)v15 <= 0x7F) {
					v16 = level->getTile(v18, v15, i);
					if(v16) {
						v14 = v16 == Tile::leaves->blockID;
					}
				} else {
					v14 = 0;
				}
			}
			++v18;
		}
		++v15;
	}
	if(!v14) {
		return 0;
	}
	v19 = level->getTile(x, y - 1, z);
	if(v19 != Tile::grass->blockID && v19 != Tile::dirt->blockID) {
		return 0;
	}
	if(y >= 120 - v31) {
		return 0;
	}
	this->placeBlock(level, x, y - 1, z, Tile::dirt->blockID);
	v20 = 0;
	while(a4 >= y + v30) {
		for(j = x - v20; j <= x + v20; ++j) {
			v22 = j - x;
			if(j - x < 0) {
				v22 = x - j;
			}
			for(a5 = z - v20; a5 <= z + v20; ++a5) {
				if(v22 != v20) {
					goto LABEL_61;
				}
				v24 = a5 - z;
				if(a5 - z < 0) {
					v24 = z - a5;
				}
				if(v24 != v22 || !v22) {
LABEL_61:
					if(!Tile::solid[level->getTile(j, a4, a5)]) {
						this->placeBlock(level, j, a4, a5, Tile::leaves->blockID, 1);
					}
				}
			}
		}
		if(v20 > 0 && a4 == y + v30 + 1) {
			--v20;
		} else if(v20 < v35) {
			++v20;
		}
		--a4;
	}
	for(k = 0; k < v31 + 6; ++k) {
		v26 = level->getTile(x, k + y, z);
		if(!v26 || v26 == Tile::leaves->blockID) {
			this->placeBlock(level, x, k + y, z, Tile::treeTrunk->blockID, 1);
		}
	}
	return 1;
}
