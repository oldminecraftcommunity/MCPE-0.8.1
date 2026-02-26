#include <tile/InvisibleTile.hpp>

InvisibleTile::InvisibleTile(int32_t id, const std::string& name, Material* mat) : Tile(id, name, mat){

}

InvisibleTile::~InvisibleTile() {
}
int32_t InvisibleTile::getRenderShape() {
	return -1;
}
