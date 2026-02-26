#include <level/gen/feature/ReedsFeature.hpp>
#include <util/Random.hpp>
#include <tile/material/Material.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>

ReedsFeature::ReedsFeature() : Feature(0){

}
ReedsFeature::~ReedsFeature() {
}
bool_t ReedsFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z) {
	int32_t v8;	 // r8
	int32_t v9;	 // r5
	int32_t v10; // r5
	int32_t v11; // r6
	int32_t v12; // r6
	int32_t v13; // r9
	int32_t v14; // r11
	int32_t v16; // [sp+8h] [bp-38h]
	int32_t v17; // [sp+10h] [bp-30h]

	v16 = 20;
	v8 = y - 1;
	do {
		v9 = x + (random->genrand_int32() & 3);
		v10 = v9 - (random->genrand_int32() & 3);
		v11 = z + (random->genrand_int32() & 3);
		v12 = v11 - (random->genrand_int32() & 3);
		if(level->isEmptyTile(v10, y, v12) && (Material::water == level->getMaterial(v10 - 1, v8, v12) || Material::water == level->getMaterial(v10 + 1, v8, v12) || Material::water == level->getMaterial(v10, v8, v12 - 1) || Material::water == level->getMaterial(v10, v8, v12 + 1))) {
			v14 = random->genrand_int32();
			v13 = 0;
			v17 = random->genrand_int32() % (v14 % 3u + 1) + 2;
			do {
				if(Tile::reeds->canSurvive(level, v10, v13 + y, v12)) {
					level->setTileNoUpdate(v10, v13 + y, v12, Tile::reeds->blockID);
				}
				++v13;
			} while(v13 < v17);
		}
		--v16;
	} while(v16);
	return 1;
}
