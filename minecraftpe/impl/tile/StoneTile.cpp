#include <tile/StoneTile.hpp>
#include <tile/material/Material.hpp>

StoneTile::StoneTile(int32_t a2, const std::string& a3)
	: Tile(a2, a3, Material::stone) {
}

StoneTile::~StoneTile() {
}
int32_t StoneTile::getResource(int32_t, struct Random*) {
	return Tile::stoneBrick->blockID;
}
