#include <level/gen/feature/SpringFeature.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>

SpringFeature::SpringFeature(int32_t id)
	: Feature(0) {
	this->id = id;
}
SpringFeature::~SpringFeature() {
}
bool_t SpringFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z){
	int32_t v9; // r8
	int32_t v10;   // r9
	Tile* v11; // r0
	int32_t v13;   // [sp+18h] [bp-30h]

	if(level->getTile(x, y + 1, z) != Tile::rock->blockID || level->getTile(x, y - 1, z) != Tile::rock->blockID || level->getTile(x, y, z) && level->getTile(x, y, z) != Tile::rock->blockID) {
		return 0;
	}
	v9 = level->getTile(x - 1, y, z) == Tile::rock->blockID;
	if(level->getTile(x + 1, y, z) == Tile::rock->blockID) {
		++v9;
	}
	v13 = z + 1;
	if(level->getTile(x, y, z - 1) == Tile::rock->blockID) {
		++v9;
	}
	if(level->getTile(x, y, v13) == Tile::rock->blockID) {
		++v9;
	}
	v10 = level->isEmptyTile(x - 1, y, z);
	if(level->isEmptyTile(x + 1, y, z)) {
		++v10;
	}
	if(level->isEmptyTile(x, y, z - 1)) {
		++v10;
	}
	if(level->isEmptyTile(x, y, v13)) {
		++v10;
	}
	if(v9 == 3 && v10 == 1) {
		level->setTile(x, y, z, this->id, 4);
		level->instantTick = 1;
		v11 = Tile::tiles[this->id];
		v11->tick(level, x, y, z, random);
		level->instantTick = 0;
	}
	return 1;
}
