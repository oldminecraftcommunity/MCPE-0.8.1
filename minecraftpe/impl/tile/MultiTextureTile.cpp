#include <tile/MultiTextureTile.hpp>

MultiTextureTile::MultiTextureTile(int32_t a2, std::string a3, const struct Material* a4)
	: Tile(a2, a4) {
	this->field_7C = *this->getTextureItem(a3);
	this->field_A8 = this->field_7C.getUVCount();
}

MultiTextureTile::~MultiTextureTile() {
}
TextureUVCoordinateSet* MultiTextureTile::getTexture(int32_t a2, int32_t a3) {
	if(a3 < 0 || a3 >= this->field_A8) {
		return &this->textureUV;
	} else {
		return this->field_7C.getUV(a3);
	}
}
int32_t MultiTextureTile::getSpawnResourcesAuxValue(int32_t a2) {
	return a2;
}
