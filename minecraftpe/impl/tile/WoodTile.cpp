#include <tile/WoodTile.hpp>
#include <tile/material/Material.hpp>

WoodTile::WoodTile(int32_t a2)
	: Tile(a2, Material::wood) {
	this->field_80 = *this->getTextureItem("planks");
}

WoodTile::~WoodTile() {
}
TextureUVCoordinateSet* WoodTile::getTexture(int32_t, int32_t a3) {
	return this->field_80.getUV(a3);
}
std::string WoodTile::getTypeDescriptionId(int32_t a3) {
	if((uint32_t)a3 > 3) a3 = 0;
	return Tile::WOOD_NAMES[a3];
}
int32_t WoodTile::getSpawnResourcesAuxValue(int32_t a2) {
	return a2;
}
