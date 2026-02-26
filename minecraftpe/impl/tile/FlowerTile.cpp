#include <tile/FlowerTile.hpp>
#include <level/Level.hpp>

bool_t FlowerTile::_randomWalk(struct Level* level, int32_t& x, int32_t& y, int32_t& z, int32_t a6) {
	Random* p_randomInstance; // r5
	int32_t i;				  // r10
	int32_t zz;				  // r3
	uint32_t v13;			  // [sp+0h] [bp-30h]

	p_randomInstance = &level->random;
	for(i = 0;; ++i) {
		if(i >= a6 / 16) {
			return a6 > 15;
		}
		x += p_randomInstance->genrand_int32() % 3 - 1;
		v13 = p_randomInstance->genrand_int32() % 3 - 1;
		y += (int32_t)(p_randomInstance->genrand_int32() % 3 * v13) / 2;
		zz = p_randomInstance->genrand_int32() % 3 - 1 + z;
		z = zz;
		if(level->getTile(x, y - 1, zz) != Tile::grass->blockID || level->isSolidBlockingTile(x, y, z)) {
			break;
		}
	}
	return 0;
}
FlowerTile::FlowerTile(int32_t id, const std::string& name)
	: Bush(id, name) {
}

FlowerTile::~FlowerTile() {
}
bool_t FlowerTile::onFertilized(Level* level, int32_t x, int32_t y, int32_t z) {
	Random* p_random; // r9
	int32_t i;		  // r6
	int8_t v10;		  // r0
	Tile* v11;		  // r4
	int32_t rx;		  // [sp+1Ch] [bp-8h] BYREF
	int32_t ry;		  // [sp+20h] [bp-4h] BYREF
	int32_t rz;		  // [sp+24h] [bp+0h] BYREF

	p_random = &level->random;
	for(i = 16; i != 64; ++i) {
		rx = x;
		ry = y + 1;
		rz = z;
		if(this->_randomWalk(level, rx, ry, rz, i) && !level->getTile(rx, ry, rz)) {
			v10 = p_random->genrand_int32();
			v11 = Tile::rose;
			if((v10 & 7) != 0) {
				if(this == Tile::rose) {
LABEL_8:
					if(v11->canSurvive(level, rx, ry, rz)) {
						level->setTileAndData(rx, ry, rz, v11->blockID, 0, 3);
					}
					continue;
				}
			} else if(this != (FlowerTile*)Tile::rose) {
				goto LABEL_8;
			}
			v11 = Tile::flower;
			goto LABEL_8;
		}
	}
	return 1;
}
