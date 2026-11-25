#include <tile/RailTile.hpp>

RailTile::RailTile(int32_t a2)
	: BaseRailTile(a2, 0) {
	this->field_84 = this->getTextureUVCoordinateSet("rail_normal_turned", 0);
}

TextureUVCoordinateSet* RailTile::getTexture(int32_t a2, int32_t a3) {
	if(a3 <= 5) {
		return &this->textureUV;
	} else {
		return &this->field_84;
	}
}
void RailTile::updateState(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8) {
	if(a8 > 0 && Tile::tiles[a8]->isSignalSource()) {
		int v15 = BaseRailTile::Rail(level, x, y, z).countPotentialConnections();
		if(v15 == 3) {
			this->updateDir(level, x, y, z, 0);
		}
	}
}
