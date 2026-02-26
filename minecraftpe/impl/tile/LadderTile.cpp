#include <tile/LadderTile.hpp>
#include <level/Level.hpp>
#include <item/ItemInstance.hpp>

LadderTile::LadderTile(int32_t id, const std::string& a3, Material* a4) : Tile(id, a3, a4){

}
LadderTile::~LadderTile() {
}
bool_t LadderTile::isCubeShaped() {
	return 0;
}
int32_t LadderTile::getRenderShape() {
	return 8;
}
AABB* LadderTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v9; // r0
	float maxZ; // r3
	float maxX; // [sp+0h] [bp-28h]

	v9 = level->getData(x, y, z);
	if(v9 != 2) {
		switch(v9) {
			case 3:
				maxX = 1.0;
				maxZ = 0.125;
				break;
			case 4:
				this->setShape(0.875, 0.0, 0.0, 1.0, 1.0, 1.0);
				return Tile::getAABB(level, x, y, z);
			case 5:
				maxX = 0.125;
				maxZ = 1.0;
				break;
			default:
				return Tile::getAABB(level, x, y, z);
		}
		this->setShape(0.0, 0.0, 0.0, maxX, 1.0, maxZ);
		return Tile::getAABB(level, x, y, z);
	}
	this->setShape(0.0, 0.0, 0.875, 1.0, 1.0, 1.0);
	return Tile::getAABB(level, x, y, z);
}
AABB LadderTile::getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v10; // r0
	float v12;	 // r3
	float v13;	 // [sp+0h] [bp-30h]

	v10 = level->getData(x, y, z);
	if(v10 != 2) {
		switch(v10) {
			case 3:
				v13 = 1.0;
				v12 = 0.125;
				break;
			case 4:
				this->setShape(0.875, 0.0, 0.0, 1.0, 1.0, 1.0);
				goto LABEL_10;
			case 5:
				v13 = 0.125;
				v12 = 1.0;
				break;
			default:
				goto LABEL_10;
		}
		this->setShape(0.0, 0.0, 0.0, v13, 1.0, v12);
		goto LABEL_10;
	}
	this->setShape(0.0, 0.0, 0.875, 1.0, 1.0, 1.0);
LABEL_10:
	return Tile::getTileAABB(level, x, y, z);
}
bool_t LadderTile::isSolidRender() {
	return 0;
}
bool_t LadderTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z, uint8_t) {
	if(level->isSolidBlockingTile(x - 1, y, z) || level->isSolidBlockingTile(x + 1, y, z) || level->isSolidBlockingTile(x, y, z - 1)) {
		return 1;
	} else {
		return level->isSolidBlockingTile(x, y, z + 1);
	}
}
void LadderTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	int32_t v13; // r0
	int32_t v14; // r0
	int32_t v15; // r1

	v13 = level->getData(x, y, z);
	if(v13 == 2) {
		v14 = level->isSolidBlockingTile(x, y, z + 1);
	} else if(v13 == 3) {
		v14 = level->isSolidBlockingTile(x, y, z - 1);
	} else {
		if(v13 == 4) {
			v15 = x + 1;
		} else {
			if(v13 != 5) {
LABEL_13:
				this->popResource(level, x, y, z, ItemInstance(Tile::ladder));
				level->setTile(x, y, z, 0, 3);
				goto LABEL_9;
			}
			v15 = x - 1;
		}
		v14 = level->isSolidBlockingTile(v15, y, z);
	}
	if(!v14) {
		goto LABEL_13;
	}
LABEL_9:
	Tile::neighborChanged(level, x, y, z, a6, a7, a8, a9);
}
int32_t LadderTile::getResourceCount(Random*) {
	return 1;
}
int32_t LadderTile::getRenderLayer() {
	return 1;
}
int32_t LadderTile::getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t side, float, float, float, Mob*, int32_t a11) {
	int32_t v12; // r4

	v12 = a11;
	if(!a11 || side == 2) {
		if(level->isSolidBlockingTile(x, y, z + 1)) {
			v12 = 2;
		} else if(!a11) {
			goto LABEL_6;
		}
	}
	if(side != 3) {
		goto LABEL_17;
	}
LABEL_6:
	if(!level->isSolidBlockingTile(x, y, z - 1)) {
LABEL_17:
		if(!v12) {
			goto LABEL_9;
		}
		goto LABEL_8;
	}
	v12 = 3;
LABEL_8:
	if(side != 4) {
		goto LABEL_11;
	}
LABEL_9:
	if(level->isSolidBlockingTile(x + 1, y, z)) {
		v12 = 4;
		goto LABEL_11;
	}
	if(v12) {
LABEL_11:
		if(side != 5) {
			return v12;
		}
	}
	if(level->isSolidBlockingTile(x - 1, y, z)) {
		return 5;
	}
	return v12;
}
