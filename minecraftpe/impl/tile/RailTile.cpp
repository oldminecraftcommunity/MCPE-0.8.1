#include <tile/RailTile.hpp>

RailTile::RailTile(int32_t a2)
	: BaseRailTile(a2, 0) {
	this->field_84 = this->getTextureUVCoordinateSet("rail_normal_turned", 0);
}

RailTile::~RailTile() {
}
TextureUVCoordinateSet* RailTile::getTexture(int32_t a2, int32_t a3) {
	if(a3 <= 5) {
		return &this->textureUV;
	} else {
		return &this->field_84;
	}
}
void RailTile::updateState(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8) {
	int32_t v12; // r1
	int32_t v13; // r2
	int32_t v14; // r3
	int32_t v15; // r9

	if(a8 > 0) {
		if(Tile::tiles[a8]->isSignalSource()) {
			v15 = BaseRailTile::Rail(level, x, y, z).countPotentialConnections();
			if(v15 == 3) {
				this->updateDir(level, x, y, z, 0);
			}
		}
	}
}
