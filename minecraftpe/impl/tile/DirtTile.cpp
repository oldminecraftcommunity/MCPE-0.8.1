#include <tile/DirtTile.hpp>

DirtTile::DirtTile(int32_t id, std::string n, Material* m)
	: Tile(id, n, m) {
	this->field_5C = 255;
}
DirtTile::~DirtTile() {
}
