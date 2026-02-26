#include <level/gen/feature/OreFeature.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>
#include <tile/Tile.hpp>
#include <util/Random.hpp>

OreFeature::OreFeature(int32_t id, int32_t amount)
	: Feature(0) {
	this->id = id;
	this->amount = amount;
}
OreFeature::~OreFeature() {
}
bool_t OreFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z) {
	int32_t v9;	  // r11
	float v10;	  // s11
	float v11;	  // s12
	float amount; // s13
	float v13;	  // s15
	float v14;	  // s23
	float v15;	  // s15
	float v16;	  // s28
	float v17;	  // s24
	float v18;	  // s28
	float v19;	  // s25
	float v20;	  // s29
	int32_t v21;  // s11
	float v22;	  // s19
	float v23;	  // s20
	float v24;	  // s21
	float v25;	  // s16
	float v26;	  // s20
	float v27;	  // s21
	float v28;	  // s19[(unsigned __int16)(int)
	int32_t i;	  // r4
	float v30;	  // s26
	int32_t j;	  // r5
	float v32;	  // s27
	int32_t k;	  // r6
	int32_t v34;  // r3
	float v36;	  // [sp+Ch] [bp-8Ch]

	v9 = 0;
	v10 = (float)(x + 8);
	v11 = (float)(random->nextFloat() * 3.1416);
	amount = (float)this->amount;
	v13 = (float)(amount * Mth::sin(v11)) * 0.125;
	v14 = v10 + v13;
	v36 = v10 - v13;
	v15 = (float)(z + 8);
	v16 = (float)(amount * Mth::cos(v11)) * 0.125;
	v17 = v15 + v16;
	v18 = v15 - v16;
	v19 = (float)(int32_t)(y + random->genrand_int32() % 3 + 2);
	v20 = (float)(int32_t)(y + random->genrand_int32() % 3 + 2);
	while(1) {
		v34 = this->amount;
		if(v9 > v34) {
			break;
		}
		v21 = this->amount;
		v22 = (float)((float)(v36 - v14) * (float)v9) / (float)v34;
		v23 = (float)((float)(v20 - v19) * (float)v9) / (float)v34;
		v24 = (float)((float)(v18 - v17) * (float)v9) / (float)v34;
		v25 = (float)((float)((float)(Mth::sin((float)((float)((float)v9 * 3.1416) / (float)v21)) + 1.0) * (float)((float)(random->nextFloat() * (float)v21) * 0.0625)) + 1.0) * 0.5;
		v26 = v19 + v23;
		v27 = v17 + v24;
		v28 = v14 + v22;
		for(i = (int32_t)(float)(v28 - v25); i <= (int32_t)(float)(v28 + v25); ++i) {
			v30 = (float)((float)((float)((float)i + 0.5) - v28) / v25) * (float)((float)((float)((float)i + 0.5) - v28) / v25);
			if(v30 < 1.0) {
				for(j = (int32_t)(float)(v26 - v25); j <= (int32_t)(float)(v26 + v25); ++j) {
					v32 = v30 + (float)((float)((float)((float)((float)j + 0.5) - v26) / v25) * (float)((float)((float)((float)j + 0.5) - v26) / v25));
					if(v32 < 1.0) {
						for(k = (int32_t)(float)(v27 - v25); k <= (int32_t)(float)(v27 + v25); ++k) {
							if((float)(v32 + (float)((float)((float)((float)((float)k + 0.5) - v27) / v25) * (float)((float)((float)((float)k + 0.5) - v27) / v25))) < 1.0 && level->getTile(i, j, k) == Tile::rock->blockID) {
								level->setTileNoUpdate(i, j, k, this->id);
							}
						}
					}
				}
			}
		}
		++v9;
	}
	return 1;
}
