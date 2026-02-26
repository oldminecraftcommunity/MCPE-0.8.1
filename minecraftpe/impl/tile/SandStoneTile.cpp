#include <tile/SandStoneTile.hpp>
#include <tile/material/Material.hpp>

SandStoneTile::SandStoneTile(int32_t a2, const std::string& a3)
	: MultiTextureTile(a2, a3, Material::stone) {
	this->field_B0 = this->getTextureUVCoordinateSet("sandstone", 3);
	this->field_C8 = this->getTextureUVCoordinateSet("sandstone", 4);

	this->field_5C = 3;

}

SandStoneTile::~SandStoneTile() {
}
TextureUVCoordinateSet* SandStoneTile::getTexture(int32_t a2, int32_t a3) {
	if(a2 == 1) {
		return &this->field_B0;
	}
	if(a2) {
		return MultiTextureTile::getTexture(a2, a3);
	}
	if(a3 > 0) {
		return &this->field_B0;
	}
	return &this->field_C8;
}
