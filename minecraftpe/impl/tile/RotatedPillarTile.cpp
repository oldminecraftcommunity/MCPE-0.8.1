#include <tile/RotatedPillarTile.hpp>

RotatedPillarTile::RotatedPillarTile(int32_t id, const struct Material* mat) : Tile(id, mat){

}
RotatedPillarTile::~RotatedPillarTile() {
}
int32_t RotatedPillarTile::getRenderShape() {
	return 31;
}
TextureUVCoordinateSet* RotatedPillarTile::getTexture(int32_t a2, int32_t a3) {
	int32_t v3; // r5
	int32_t v5; // r1

	v3 = a3 & 0xC;
	if((a3 & 0xC) == 0) {
		if((uint32_t)a2 <= 1) {
			return this->getDirTexture(a3 & 0xC, a3);
		}
		return this->getDirTexture(5, a3);
	}
	if(v3 == 4) {
		v5 = a2 - 4;
	} else {
		if(v3 != 8) {
			return this->getDirTexture(5, a3);
		}
		v5 = a2 - 2;
	}
	if((uint32_t)v5 <= 1) {
		return this->getDirTexture(0, a3);
	}
	return this->getDirTexture(5, a3);
}
int8_t byte_D6753BF4[] = {8, 8, 4, 4};
int32_t RotatedPillarTile::getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, float a7, float a8, float a9, Mob* a10, int32_t a11) {
	int32_t v11; // r3

	if((uint32_t)(a6 - 2) > 3) {
		v11 = 0;
	} else {
		v11 = byte_D6753BF4[a6 - 2];
	}
	return a11 & 3 | v11;
}
TextureUVCoordinateSet* RotatedPillarTile::getDirTexture(int32_t, int32_t) {
	return &this->textureUV;
}
