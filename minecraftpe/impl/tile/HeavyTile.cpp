#include <tile/HeavyTile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <entity/FallingTile.hpp>

bool_t HeavyTile::instaFall = 0;

HeavyTile::HeavyTile(int32_t id, const std::string& a2)
	: HeavyTile(id, a2, Material::sand) {
}
HeavyTile::HeavyTile(int32_t a2, const std::string& a3, const Material* a4)
	: Tile(a2, a3, a4){

}

void HeavyTile::checkSlide(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v8; // r4
	int32_t a7; // r10
	FallingTile* v10; // r9

	v8 = y;
	if(HeavyTile::isFree(level, x, y - 1, z) && v8 >= 0) {
		if(!HeavyTile::instaFall && level->hasChunksAt(x - 32, v8 - 32, z - 32, x + 32, v8 + 32, z + 32)) {
			if(!level->isClientMaybe) {
				a7 = level->getData(x, v8, z);
				v10 = new FallingTile(level, (float)x + 0.5, (float)v8 + 0.5, (float)z + 0.5, this->blockID, a7);
				this->falling(v10);
				level->addEntity(v10);
			}
		} else {
			level->setTile(x, v8, z, 0, 3);
			while(HeavyTile::isFree(level, x, v8 - 1, z)) {
				if(!v8) {
					return;
				}
				--v8;
			}
			if(v8) {
				level->setTile(x, v8, z, this->blockID, 3);
			}
		}
	}
}

bool_t HeavyTile::isFree(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v4; // r0
	const Material* material; // r3
	bool_t result; // r0

	v4 = level->getTile(x, y, z);
	result = !v4 || v4 == Tile::fire->blockID || (material = Tile::tiles[v4]->material, material == Material::water) || material == Material::lava;
	return result;
}

HeavyTile::~HeavyTile() {
}
int32_t HeavyTile::getTickDelay() {
	return 2;
}
void HeavyTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
	if(!level->isClientMaybe) {
		this->checkSlide(level, x, y, z);
	}
}
void HeavyTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
	level->addToTickNextTick(x, y, z, this->blockID, this->getTickDelay());
}
void HeavyTile::onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	level->addToTickNextTick(x, y, z, this->blockID, this->getTickDelay());
}

void HeavyTile::falling(struct FallingTile*) {
}
void HeavyTile::onLand(Level*, int32_t, int32_t, int32_t, int32_t) {
}
