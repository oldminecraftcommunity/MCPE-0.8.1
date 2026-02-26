#include <tile/ClothTile.hpp>
#include <tile/material/Material.hpp>

ClothTile::ClothTile(int32_t id)
	: Tile(id, Material::cloth) {
	this->tex = *this->getTextureItem("wool");
	this->textureUV = *this->tex.getUV(0);
}

ClothTile::~ClothTile() {
}
TextureUVCoordinateSet* ClothTile::getTexture(int32_t a2, int32_t a3) {
	if(a3) return this->tex.getUV(a3);
	return &this->textureUV;
}
int32_t ClothTile::getSpawnResourcesAuxValue(int32_t a2) {
	return a2;
}
