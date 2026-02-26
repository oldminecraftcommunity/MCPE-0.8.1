#include <tile/PoweredRailTile.hpp>
#include <level/Level.hpp>

PoweredRailTile::PoweredRailTile(int32_t id)
	: BaseRailTile(id, 1) {
	this->textureUV = this->getTextureUVCoordinateSet("rail_golden", 0);
	this->poweredRailTexture = this->getTextureUVCoordinateSet("rail_golden_powered", 0);
}
bool_t PoweredRailTile::findPoweredRailSignal(Level* level, int32_t x, int32_t y, int32_t z, bool_t a6, int32_t a7, int32_t a8) {
	if(level->getTile(x, y, z) == this->blockID) {
		level->getData(x, y, z);
	}
	return 0;
}
bool_t PoweredRailTile::isSameRailWithPower(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, bool_t a7, int32_t a8) {
	int32_t v8;	 // r8
	int32_t v11; // r7
	int32_t v12; // r9
	int32_t v13; // r4
	int32_t v14; // r5

	v8 = x;
	v11 = y;
	v12 = z;
	if(a8 > 7) {
		return 0;
	}
	v13 = a6 & 7;
	switch(a6 & 7) {
		case 0:
			if(!a7) {
				goto LABEL_5;
			}
			goto LABEL_4;
		case 1:
			if(a7) {
				goto LABEL_8;
			}
			goto LABEL_9;
		case 2:
			if(a7) {
LABEL_8:
				v8 = x - 1;
				goto LABEL_10;
			}
			v8 = x + 1;
			goto LABEL_15;
		case 3:
			if(!a7) {
LABEL_9:
				v8 = x + 1;
LABEL_10:
				v14 = 1;
				goto LABEL_20;
			}
			v8 = x - 1;
LABEL_15:
			v11 = y + 1;
			v14 = 0;
			v13 = 1;
			return this->isSameRailWithPower(level, v8, v11, v12, a7, a8, v13) || v14 && this->isSameRailWithPower(level, v8, v11 - 1, v12, a7, a8, v13);
		case 4:
			if(a7) {
LABEL_4:
				v12 = z + 1;
				goto LABEL_6;
			}
			v12 = z - 1;
			v11 = y + 1;
			v14 = 0;
			v13 = 0;
			break;
		case 5:
			if(a7) {
				v12 = z + 1;
				v11 = y + 1;
				v14 = 0;
LABEL_20:
				v13 = v14;
			} else {
LABEL_5:
				v12 = z - 1;
LABEL_6:
				v14 = 1;
				v13 = 0;
			}
			break;
		default:
			v14 = 1;
			return this->isSameRailWithPower(level, v8, v11, v12, a7, a8, v13) || v14 && this->isSameRailWithPower(level, v8, v11 - 1, v12, a7, a8, v13);
	}
	return this->isSameRailWithPower(level, v8, v11, v12, a7, a8, v13) || v14 && this->isSameRailWithPower(level, v8, v11 - 1, v12, a7, a8, v13);
}

PoweredRailTile::~PoweredRailTile() {
}
TextureUVCoordinateSet* PoweredRailTile::getTexture(int32_t) {
	return &this->poweredRailTexture;
}
TextureUVCoordinateSet* PoweredRailTile::getTexture(int32_t, int32_t) {
	return &this->poweredRailTexture;
}
void PoweredRailTile::updateState(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8){
	if(level->hasNeighborSignal(x, y, z) || this->findPoweredRailSignal(level, x, y, z, a6, 1, 0) || this->findPoweredRailSignal(level, x, y, z, a6, 0, 0)) {
		level->setData(x, y, z, a7, 3);
		level->updateNeighborsAt(x, y - 1, z, this->blockID);
		if((uint32_t)(a7 - 2) <= 3) {
			level->updateNeighborsAt(x, y + 1, z, this->blockID);
		}
	}
}
