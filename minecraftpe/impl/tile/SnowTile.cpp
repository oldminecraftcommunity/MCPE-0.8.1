#include <tile/SnowTile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <level/LightLayer.hpp>

SnowTile::SnowTile(int32_t id, const std::string& name, Material* mat)
	: Tile(id, name, mat) {
	this->setTicking(1);
	this->field_5C = 255;
}

SnowTile::~SnowTile() {
}
void SnowTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
	if(level->getBrightness(LightLayer::Block, x, y, z) > 11) {
		this->spawnResources(level, x, y, z, level->getData(x, y, z), 0);
		level->setTile(x, y, z, 0, 3);
	}
}
int32_t SnowTile::getResource(int32_t, Random*) {
	return Item::snowBall->itemID;
}
int32_t SnowTile::getResourceCount(Random*) {
	return 4;
}
