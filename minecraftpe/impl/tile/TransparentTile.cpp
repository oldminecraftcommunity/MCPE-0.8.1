#include <tile/TransparentTile.hpp>
#include <level/LevelSource.hpp>

TransparentTile::TransparentTile(int32_t id, const std::string& s, Material* mat)
	: Tile(id, s, mat) {
	this->field_7C = 0; //TODO check is it actually here
}

TransparentTile::~TransparentTile() {
}
bool_t TransparentTile::shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t face) {
	int32_t v10; // r0

	v10 = level->getTile(x, y, z);
	if(!this->field_7C && v10 == this->blockID) {
		return this->field_7C;
	} else {
		return Tile::shouldRenderFace(level, x, y, z, face);
	}
}
bool_t TransparentTile::isSolidRender() {
	return 0;
}
