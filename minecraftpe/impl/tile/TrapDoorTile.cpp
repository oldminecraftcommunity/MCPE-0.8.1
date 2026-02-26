#include <tile/TrapDoorTile.hpp>
#include <tile/material/Material.hpp>
#include <level/Level.hpp>
#include <item/ItemInstance.hpp>
#include <math/HitResult.hpp>

TrapDoorTile::TrapDoorTile(int32_t id, const struct Material* mat)
	: Tile(id, mat) {
	this->textureUV = this->getTextureUVCoordinateSet("trapdoor", 0);

	this->textureUV = this->getTextureUVCoordinateSet(mat == Material::wood ? "trapdoor" : "iron_bars", 0);
	this->setShape(0, 0, 0, 1, 1, 1);
}

void TrapDoorTile::_setShape(int32_t meta) {
	int32_t v4; // r6

	this->setShape(0.0, 0.0, 0.0, 1.0, 0.1875, 1.0);
	if(TrapDoorTile::isOpen(meta)) {
		v4 = meta & 3;
		if(v4) {
			if(v4 == 1) {
				this->setShape(0.0, 0.0, 0.0, 1.0, 1.0, 0.1875);
			} else if(v4 == 2) {
				this->setShape(0.8125, 0.0, 0.0, 1.0, 1.0, 1.0);
			} else {
				this->setShape(0.0, 0.0, 0.0, 0.1875, 1.0, 1.0);
			}
		} else {
			this->setShape(0.0, 0.0, 0.8125, 1.0, 1.0, 1.0);
		}
	}
}
bool_t TrapDoorTile::attachesTo(int32_t a1) {
	Tile* tile; // r4
	int32_t v2; // r6

	if(a1 <= 0) {
		return 0;
	}
	tile = Tile::tiles[a1];
	if(!tile) {
		return 0;
	}
	v2 = tile->getRenderShape();
	return tile->material->isSolidBlocking() && tile->isCubeShaped() || tile == Tile::lightGem || tile == Tile::stoneSlabHalf || tile == Tile::woodSlabHalf || v2 == 10;
}
bool_t TrapDoorTile::blocksLight(void) {
	return 0;
}
int32_t TrapDoorTile::getDir(int32_t a2) {
	if((a2 & 4) == 0) {
		//LOBYTE(a2) = a2 - 1;
		a2 = a2 - 1;
	}
	return a2 & 3;
}
bool_t TrapDoorTile::isOpen(int32_t a1) {
	return ((uint32_t)a1 >> 2) & 1;
}
void TrapDoorTile::setOpen(Level* level, int32_t x, int32_t y, int32_t z, bool_t open) {
	uint32_t v9; // r0

	v9 = level->getData(x, y, z);
	if(((v9 >> 2) & 1) != open) {
		level->setData(x, y, z, v9 ^ 4, 2);
		level->levelEvent(0, 1003, x, y, z, 0);
	}
}

TrapDoorTile::~TrapDoorTile() {
}
bool_t TrapDoorTile::isCubeShaped() {
	return 0;
}
int32_t TrapDoorTile::getRenderShape() {
	return 0;
}
void TrapDoorTile::updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t v6 = level->getData(x, y, z);
	this->_setShape(v6);
}
void TrapDoorTile::updateDefaultShape() {
	this->setShape(0.0, 0.40625, 0.0, 1.0, 0.59375, 1.0);
}
AABB* TrapDoorTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->updateShape(level, x, y, z);
	return Tile::getAABB(level, x, y, z);
}
AABB TrapDoorTile::getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->updateShape(level, x, y, z);
	return Tile::getTileAABB(level, x, y, z);
}
bool_t TrapDoorTile::isSolidRender() {
	return 0;
}
bool_t TrapDoorTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z, uint8_t a6) {
	int32_t v7; // r3
	int32_t v8; // r0

	v7 = z;
	switch(a6) {
		case 0u:
		case 1u:
			return 0;
		case 2u:
			v7 = z + 1;
			break;
		case 3u:
			v7 = z - 1;
			break;
		case 4u:
			++x;
			break;
		case 5u:
			--x;
			break;
	}
	v8 = level->getTile(x, y, v7);
	return TrapDoorTile::attachesTo(v8);
}
void TrapDoorTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	int32_t v13; // r0
	int32_t v14; // r3
	int32_t v15; // r1
	int32_t v16; // r0
	int32_t hasNeighborSignal; // r0
	bool_t v18; // r11

	if(!level->isClientMaybe) {
		v13 = level->getData(x, y, z) & 3;
		if(v13) {
			if(v13 != 1) {
				if(v13 == 2) {
					v15 = x + 1;
				} else {
					v15 = x - 1;
				}
				v14 = z;
LABEL_11:
				v16 = level->getTile(v15, y, v14);
				if(!TrapDoorTile::attachesTo(v16)) {
					level->setTile(x, y, z, 0, 3);
					this->popResource(level, x, y, z, ItemInstance(Tile::trapdoor));
				}
				hasNeighborSignal = level->hasNeighborSignal(x, y, z);
				v18 = hasNeighborSignal;
				if(!hasNeighborSignal) {
					if(a9 <= 0) {
						if(a9) {
							return;
						}
					} else if(!Tile::tiles[a9]->isSignalSource()) {
						return;
					}
				}
				this->setOpen(level, x, y, z, v18);
				return;
			}
			v14 = z - 1;
		} else {
			v14 = z + 1;
		}
		v15 = x;
		goto LABEL_11;
	}
}
HitResult TrapDoorTile::clip(Level* level, int32_t x, int32_t y, int32_t z, const Vec3& a6, const Vec3& a7) {
	this->updateShape(level, x, y, z);
	return Tile::clip(level, x, y, z, a6, a7);
}
int32_t TrapDoorTile::getRenderLayer() {
	return 1;
}
bool_t TrapDoorTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	int32_t v9; // r0

	if(this->material != Material::metal) {
		v9 = level->getData(x, y, z);
		level->setData(x, y, z, v9 ^ 4, 2);
		level->levelEvent(player, 1003, x, y, z, 0);
	}
	return 1;
}
int32_t TrapDoorTile::getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, float, float, float, Mob*, int32_t) {
	switch(a6) {
		case 3:
			return 1;
		case 4:
			return 2;
		case 5:
			return 3;
	}
	return 0;
}
void TrapDoorTile::attack(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	this->use(level, x, y, z, player);
}
