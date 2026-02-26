#include <level/gen/feature/CactusFeature.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
CactusFeature::CactusFeature() : Feature(0){

}
CactusFeature::~CactusFeature() {
}
bool_t CactusFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z) {
	uint32_t v8;  // r7
	int32_t v9;	  // r7
	uint32_t v10; // r9
	int32_t v11;  // r9
	uint32_t v12; // r8
	int32_t v13;  // r8
	uint32_t v14; // r10
	int32_t v15;  // r6
	int32_t v17;  // [sp+8h] [bp-38h]
	int32_t v18;  // [sp+10h] [bp-30h]

	v17 = 10;
	do {
		v8 = x + (random->genrand_int32() & 7);
		v9 = v8 - (random->genrand_int32() & 7);
		v10 = y + (random->genrand_int32() & 3);
		v11 = v10 - (random->genrand_int32() & 3);
		v12 = z + (random->genrand_int32() & 7);
		v13 = v12 - (random->genrand_int32() & 7);
		if(level->isEmptyTile(v9, v11, v13)) {
			v14 = random->genrand_int32();
			v15 = 0;
			v18 = random->genrand_int32() % (v14 % 3 + 1);
			do {
				if(Tile::cactus->canSurvive(level, v9, v15 + v11, v13)) {
					level->setTileNoUpdate(v9, v15 + v11, v13, Tile::cactus->blockID);
				}
				++v15;
			} while(v18 >= v15);
		}
		--v17;
	} while(v17);
	return 1;
}
