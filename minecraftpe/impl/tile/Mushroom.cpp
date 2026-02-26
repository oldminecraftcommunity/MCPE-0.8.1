#include <tile/Mushroom.hpp>
#include <level/Level.hpp>

Mushroom::Mushroom(int32_t id, const std::string& name) : Bush(id, name){
	this->setShape(0.3, 0.0, 0.3, 0.7, 0.4, 0.7);
	this->setTicking(1);
}

Mushroom::~Mushroom() {
}
bool_t Mushroom::mayPlace(Level* level, int32_t x, int32_t y, int32_t z, uint8_t a6) {
	if(Tile::mayPlace(level, x, y, z, a6)) {
		return this->canSurvive(level, x, y, z);
	}
	return 0;
}
void Mushroom::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
	int32_t v8;	  // r10
	int32_t i;	  // r8
	int32_t j;	  // r9
	int32_t k;	  // r7
	uint32_t v12; // r7
	uint32_t v13; // r8
	int32_t v14;  // r8
	int32_t v15;  // r9
	int32_t v16;  // r11
	uint32_t v17; // r10
	uint32_t v18; // r10
	uint32_t v19; // r1
	bool_t v20;	  // zf
	uint32_t v21; // r1
	int32_t v22;  // [sp+Ch] [bp-3Ch]
	int32_t v25;  // [sp+18h] [bp-30h]
	int32_t v26;  // [sp+1Ch] [bp-2Ch]

	v25 = z;
	if(!(random->genrand_int32() % 0x19)) {
		v8 = 5;
		for(i = x - 4; i <= x + 4; ++i) {
			for(j = z - 4; j <= z + 4; ++j) {
				for(k = y - 1; k <= y + 1; ++k) {
					if(level->getTile(i, k, j) == this->blockID && --v8 <= 0) {
						return;
					}
				}
			}
		}
		v12 = x + random->genrand_int32() % 3 - 1;
		v13 = y + (random->genrand_int32() & 1);
		v14 = v13 - (random->genrand_int32() & 1);
		v26 = 4;
		v15 = z + random->genrand_int32() % 3 - 1;
		while(1) {
			if(!level->isEmptyTile(v12, v14, v15) || !this->canSurvive(level, v12, v14, v15)) {
				v12 = x;
				v14 = y;
				v15 = v25;
			}
			v16 = v12 + random->genrand_int32() % 3 - 1;
			v17 = v14 + (random->genrand_int32() & 1);
			v18 = v17 - (random->genrand_int32() & 1);
			v19 = random->genrand_int32() % 3;
			v20 = v26-- == 1;
			v21 = v19 + v15;
			if(v20) {
				break;
			}
			v25 = v15;
			v15 = v21 - 1;
			y = v14;
			v14 = v18;
			x = v12;
			v12 = v16;
		}
		v22 = v21 - 1;
		if(level->isEmptyTile(v16, v18, v21 - 1)) {
			if(this->canSurvive(level, v16, v18, v22)) {
				level->setTile(v16, v18, v22, this->blockID, 3);
			}
		}
	}
}
bool_t Mushroom::canSurvive(Level* level, int32_t x, int32_t y, int32_t z){
	int32_t v9; // r9

	if((uint32_t)y > 0x7F) {
		return 0;
	}
	v9 = level->getTile(x, y - 1, z);
	return level->getRawBrightness(x, y, z) <= 12 && this->mayPlaceOn(v9);
}
bool_t Mushroom::mayPlaceOn(int32_t a2) {
	return Tile::solid[a2];
}
