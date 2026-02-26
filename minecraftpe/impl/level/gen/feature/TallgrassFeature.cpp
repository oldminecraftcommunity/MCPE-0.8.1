#include <level/gen/feature/TallgrassFeature.hpp>
#include <util/Random.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>

TallgrassFeature::TallgrassFeature(int32_t blockID, int32_t c)
	: Feature(0) {
	this->blockID = blockID;
	this->field_C = c;
}
TallgrassFeature::~TallgrassFeature() {
}
bool_t TallgrassFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z){
	int32_t v10; // r0
	int32_t v11; // r11
	int32_t v12; // r11
	int32_t v13; // r10
	int32_t v14; // r10
	int32_t v15; // r9
	int32_t v16; // r9
	Tile* v17;	 // r0
	int32_t v19; // [sp+8h] [bp-30h]

	while(1) {
		v10 = level->getTile(x, y, z);
		if(v10) {
			if(v10 != Tile::leaves->blockID) {
				break;
			}
		}
		if(y <= 0) {
			break;
		}
		--y;
	}
	v19 = 128;
	do {
		v11 = x + (random->genrand_int32() & 7);
		v12 = v11 - (random->genrand_int32() & 7);
		v13 = y + (random->genrand_int32() & 3);
		v14 = v13 - (random->genrand_int32() & 3);
		v15 = z + (random->genrand_int32() & 7);
		v16 = v15 - (random->genrand_int32() & 7);
		if(level->isEmptyTile(v12, v14, v16)) {
			v17 = Tile::tiles[this->blockID];
			if(v17->canSurvive(level, v12, v14, v16)) {
				level->setTileAndDataNoUpdate(v12, v14, v16, this->blockID, this->field_C);
			}
		}
		--v19;
	} while(v19);
	return 1;
}
