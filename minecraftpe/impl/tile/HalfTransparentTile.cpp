#include <tile/HalfTransparentTile.hpp>
#include <level/LevelSource.hpp>

HalfTransparentTile::HalfTransparentTile(int32_t id, const std::string& s, Material* m)
	: Tile(id, s, m) {
	this->field_80 = 0;
}
HalfTransparentTile::~HalfTransparentTile() {
}
bool_t HalfTransparentTile::shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t side) {
	int32_t id = level->getTile(x, y, z);
	if(!this->field_80 && id == this->blockID) return this->field_80;
	return Tile::shouldRenderFace(level, x, y, z, side);
}
bool_t HalfTransparentTile::isSolidRender() {
	return 0;
}
int32_t HalfTransparentTile::getRenderLayer() {
	return 2;
}
