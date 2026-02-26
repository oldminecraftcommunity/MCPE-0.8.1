#include <tile/IceTile.hpp>
#include <level/Level.hpp>
#include <level/LightLayer.hpp>
#include <tile/material/Material.hpp>

IceTile::IceTile(int32_t id, const std::string& n, Material* m)
	: Tile(id, n, m) {
	this->slipperiness = 0.98;
	this->setTicking(1);
}

IceTile::~IceTile() {
}
void IceTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* r) {
	int32_t v11; // r0

	if(level->getBrightness(LightLayer::Block, x, y, z) > 11 - Tile::lightBlock[this->blockID]) {
		v11 = level->getData(x, y, z);
		this->spawnResources(level, x, y, z, v11);
		level->setTile(x, y, z, Tile::calmWater->blockID, 3);
	}
}
int32_t IceTile::getResourceCount(Random*) {
	return 0;
}
void IceTile::playerDestroy(Level* level, Player* player, int32_t x, int32_t y, int32_t z, int32_t) {
	Material* v9; // r5

	v9 = level->getMaterial(x, y - 1, z);
	if(v9->blocksMotion() || v9->isLiquid()) {
		level->setTile(x, y, z, Tile::water->blockID, 3);
	}
}
