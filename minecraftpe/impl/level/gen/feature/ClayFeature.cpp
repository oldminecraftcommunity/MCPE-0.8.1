#include <level/gen/feature/ClayFeature.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <math.h>
#include <tile/Tile.hpp>
ClayFeature::ClayFeature()
	: Feature(0) {
	this->size = 32;
	this->id = Tile::clay->blockID;
}
ClayFeature::~ClayFeature() {
}
bool_t ClayFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z) {
	int32_t v11; // r8
	double v12;	 // d8
	double v13;	 // d11
	double v14;	 // r0
	double size;	 // d10
	double v16;	 // d7
	float v17;	 // s24
	float v18;	 // s25
	double v19;	 // d8
	double v20;	 // d9
	float v21;	 // s27
	float v22;	 // s18
	float v23;	 // s28
	float v24;	 // s20
	float v26;	 // s21
	float v27;	 // s22
	float v28;	 // s23
	float Float; // r0
	int32_t v30; // s12
	float v31;	 // s21
	float v32;	 // s19
	float v33;	 // s19
	int32_t v34; // r4
	float v35;	 // s22
	float v36;	 // s23
	int32_t i;	 // r5
	int32_t j;	 // r6
	int32_t v39; // r3

	if(Material::water != level->getMaterial(x, y, z)) {
		return 0;
	}
	v11 = 0;
	v12 = (double)(x + 8);
	v13 = (float)(random->nextFloat() * 3.1416);
	v14 = sin(v13);
	size = (double)this->size;
	v16 = v14 * size * 0.125;
	v17 = v12 + v16;
	v18 = v12 - v16;
	v19 = (double)(z + 8);
	v20 = cos(v13) * size * 0.125;
	v21 = v19 + v20;
	v22 = v19 - v20;
	v23 = (float)(int32_t)(y + random->genrand_int32() % 3 + 2);
	v24 = (float)(int32_t)(y + random->genrand_int32() % 3 + 2);
	while(1) {
		v39 = this->size;
		if(v11 > v39) {
			break;
		}
		v26 = (float)((float)(v18 - v17) * (float)v11) / (float)v39;
		v27 = (float)((float)(v24 - v23) * (float)v11) / (float)v39;
		v28 = (float)((float)(v22 - v21) * (float)v11) / (float)v39;
		Float = random->nextFloat();
		v30 = this->size;
		v31 = v17 + v26;
		v32 = (sin((float)((float)((float)v11 * 3.1416) / (float)v30)) + 1.0) * (float)(Float * (float)(v30 >> 4)) + 1.0;
		v33 = v32 * 0.5;
		v34 = (int32_t)(float)(v31 - v33);
		v35 = v23 + v27;
		v36 = v21 + v28;
		while(v34 <= (int32_t)(float)(v31 + v33)) {
			for(i = (int32_t)(float)(v35 - v33); i <= (int32_t)(float)(v35 + v33); ++i) {
				for(j = (int32_t)(float)(v36 - v33); j <= (int32_t)(float)(v36 + v33); ++j) {
					if((float)((float)((float)((float)((float)((float)((float)i + 0.5) - v35) / v33) * (float)((float)((float)((float)i + 0.5) - v35) / v33)) + (float)((float)((float)((float)((float)v34 + 0.5) - v31) / v33) * (float)((float)((float)((float)v34 + 0.5) - v31) / v33))) + (float)((float)((float)((float)((float)j + 0.5) - v36) / v33) * (float)((float)((float)((float)j + 0.5) - v36) / v33))) < 1.0 && level->getTile(v34, i, j) == Tile::sand->blockID) {
						level->setTileNoUpdate(v34, i, j, this->id);
					}
				}
			}
			++v34;
		}
		++v11;
	}
	return 1;
}
