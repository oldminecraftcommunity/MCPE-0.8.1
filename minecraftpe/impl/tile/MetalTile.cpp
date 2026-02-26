#include <tile/MetalTile.hpp>
#include <tile/material/Material.hpp>

MetalTile::MetalTile(int32_t id, const std::string& a3) : Tile(id, a3, Material::metal){

}

MetalTile::~MetalTile() {
}
TextureUVCoordinateSet* MetalTile::getTexture(int32_t) {
	return &this->textureUV;
}
