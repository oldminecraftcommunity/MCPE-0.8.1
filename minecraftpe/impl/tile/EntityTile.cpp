#include <tile/EntityTile.hpp>
#include <level/Level.hpp>
#include <tile/entity/TileEntity.hpp>
#include <tile/entity/TileEntityFactory.hpp>

EntityTile::EntityTile(int32_t id, const struct Material* mat)
	: Tile(id, mat) {
	Tile::isEntityTile[this->blockID] = 1;
}
EntityTile::EntityTile(int32_t id, const std::string& s, const struct Material* mat) : Tile(id, s, mat){
	Tile::isEntityTile[this->blockID] = 1;
}

EntityTile::~EntityTile() {
}
void EntityTile::onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	level->setTileEntity(x, y, z, this->newTileEntity());
}

void EntityTile::onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
	level->removeTileEntity(x, y, z);
}
void EntityTile::triggerEvent(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7) {
	TileEntity* res = level->getTileEntity(x, y, z);
	if(res) {
		res->triggerEvent(a6, a7);
	}
}
struct TileEntity* EntityTile::newTileEntity() {
	return TileEntityFactory::createTileEntity(this->getTileEntityType());
}
