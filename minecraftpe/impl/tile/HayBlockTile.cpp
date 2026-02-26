#include <tile/HayBlockTile.hpp>
#include <tile/material/Material.hpp>

HayBlockTile::HayBlockTile(int32_t id)
	: RotatedPillarTile(id, Material::dirt) {
	this->field_80 = this->getTextureUVCoordinateSet("hayblock", 0);
	this->field_98 = this->getTextureUVCoordinateSet("hayblock", 1);
}
HayBlockTile::~HayBlockTile() {
}
TextureUVCoordinateSet* HayBlockTile::getDirTexture(int32_t a2, int32_t a3) {
	if(a2) {
		return &this->field_98;
	} else {
		return &this->field_80;
	}
}
