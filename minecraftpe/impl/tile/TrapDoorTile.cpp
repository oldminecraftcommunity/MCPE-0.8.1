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

	Tile::setShape(0.0f, 0.0f, 0.0f, 1.0f, 0.1875f, 1.0f);
	if(TrapDoorTile::isOpen(meta)) {
		int v4 = meta & 3;
		if(v4 == 0) Tile::setShape(0.0f, 0.0f, 0.8125f, 1.0f, 1.0f, 1.0f);
		if(v4 == 1) Tile::setShape(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.1875f);
		if(v4 == 2) Tile::setShape(0.8125f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		if(v4 == 3) Tile::setShape(0.0f, 0.0f, 0.0f, 0.1875f, 1.0f, 1.0f);
	}
}
bool_t TrapDoorTile::attachesTo(int32_t a1) {
	if(a1 <= 0) return 0;

	Tile* tile = Tile::tiles[a1];
	if(!tile) return 0;

	int v2 = tile->getRenderShape();
	return tile->material->isSolidBlocking() && tile->isCubeShaped() || tile == Tile::lightGem || tile == Tile::stoneSlabHalf || tile == Tile::woodSlabHalf || v2 == 10;
}
bool_t TrapDoorTile::blocksLight(void) {
	return 0;
}
int32_t TrapDoorTile::getDir(int32_t a2) {
	if((a2 & 4) == 0) {
		a2 -= 1;
	}
	return a2 & 3;
}
bool_t TrapDoorTile::isOpen(int32_t a1) {
	return ((uint32_t)a1 >> 2) & 1;
}
void TrapDoorTile::setOpen(Level* level, int32_t x, int32_t y, int32_t z, bool_t open) {

	uint32_t v9 = level->getData(x, y, z);
	if(((v9 >> 2) & 1) != open) {
		level->setData(x, y, z, v9 ^ 4, 2);
		level->levelEvent(0, 1003, x, y, z, 0);
	}
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
	this->setShape(0.0f, 0.40625f, 0.0f, 1.0f, 0.59375f, 1.0f);
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
	if(a6 == 0) return 0;
	if(a6 == 1) return 0;

	if(a6 == 2) ++z;
	if(a6 == 3) --z;
	if(a6 == 4) ++x;
	if(a6 == 5) --x;

	int v8 = level->getTile(x, y, z);
	return TrapDoorTile::attachesTo(v8);
}
void TrapDoorTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	int32_t v13; // r0
	int32_t v14; // r3
	int32_t v15; // r1
	int32_t v16; // r0
	int32_t hasNeighborSignal; // r0
	bool_t v18; // r11

	if(!level->isClient) {
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
