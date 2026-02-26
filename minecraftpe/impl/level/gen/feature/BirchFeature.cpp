#include <level/gen/feature/BirchFeature.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>

BirchFeature::BirchFeature(bool_t u) : Feature(u){

}

BirchFeature::~BirchFeature() {
}
bool_t BirchFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z) {
	int32_t v9;	 // r7
	bool_t v10;	 // r9
	int32_t v11; // r8
	int32_t i;	 // r11
	int32_t v13; // r0
	int32_t j;	 // r10
	int32_t v15; // r0
	int32_t k;	 // r7
	int32_t v17; // r10
	int32_t m;	 // r8
	int32_t v19; // r9
	int32_t v20; // r3
	int32_t v21; // r7
	int32_t v22; // r0
	int32_t v23; // [sp+14h] [bp-4Ch]
	int32_t v24; // [sp+14h] [bp-4Ch]
	int32_t v25; // [sp+18h] [bp-48h]
	int32_t v26; // [sp+1Ch] [bp-44h]
	int32_t v27; // [sp+20h] [bp-40h]

	v23 = random->genrand_int32() % 3;
	v25 = v23 + 5;
	if(y <= 0) {
		return 0;
	}
	v27 = y + v25;
	if(y + v25 > 127) {
		return 0;
	}
	v9 = y;
	v10 = 1;
	v26 = y + 1 + v25;
	while(v9 <= v26) {
		if(v9 >= v26 - 2) {
			v11 = 2;
		} else {
			v11 = v9 != y;
		}
		for(i = x - v11; i <= x + v11 && v10; ++i) {
			for(j = z - v11; j <= z + v11 && v10; ++j) {
				if((unsigned int)v9 <= 0x7F) {
					v13 = level->getTile(i, v9, j);
					if(v13) {
						v10 = v13 == Tile::leaves->blockID;
					}
				} else {
					v10 = 0;
				}
			}
		}
		++v9;
	}
	if(!v10) {
		return 0;
	}
	v15 = level->getTile(x, y - 1, z);
	if(v15 != Tile::grass->blockID && v15 != Tile::dirt->blockID) {
		return 0;
	}
	if(y >= 122 - v23) {
		return 0;
	}
	this->placeBlock(level, x, y - 1, z, Tile::dirt->blockID);
	for(k = y - 3 + v25; k <= v27; ++k) {
		v17 = 1 - (k - v27) / 2;
		for(m = x - v17; m <= x + v17; ++m) {
			v19 = z - v17;
			v24 = /*abs32*/ abs(m - x);
			while(v19 <= z + v17) {
				if(v24 != v17) {
					goto LABEL_53;
				}
				v20 = v19 - z;
				if(v19 - z < 0) {
					v20 = z - v19;
				}
				if(v20 != v24 || (random->genrand_int32() & 1) != 0 && k != v27) {
LABEL_53:
					if(!Tile::solid[level->getTile(m, k, v19)]) {
						this->placeBlock(level, m, k, v19, Tile::leaves->blockID, 2);
					}
				}
				++v19;
			}
		}
	}
	v21 = 0;
	do {
		v22 = level->getTile(x, v21 + y, z);
		if(!v22 || v22 == Tile::leaves->blockID) {
			this->placeBlock(level, x, v21 + y, z, Tile::treeTrunk->blockID, 2);
		}
		++v21;
	} while(v21 < v25);
	return 1;
}
