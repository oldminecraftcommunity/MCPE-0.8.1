#include <tile/ClayTile.hpp>
#include <item/Item.hpp>

ClayTile::ClayTile(int32_t id, std::string n, Material* m)
	: Tile(id, n, m) {
	this->field_5C = 255;
}

ClayTile::~ClayTile() {
}
int32_t ClayTile::getResource(int32_t, Random*) {
	return Item::clay->itemID;
}
int32_t ClayTile::getResourceCount(Random*) {
	return 4;
}
