#include <tile/FenceGateTile.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

FenceGateTile::FenceGateTile(int32_t id, const std::string& n, Material* mat)
	: Tile(id, n, mat) {
}
FenceGateTile::~FenceGateTile() {
}
bool_t FenceGateTile::isCubeShaped() {
	return 0;
}
int32_t FenceGateTile::getRenderShape() {
	return 21;
}
AABB* FenceGateTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v8;  // r0
	float v9;	// s13
	float v10;	// s14
	float v11;	// s15
	float v12;	// s15

	v8 = level->getData(x, y, z);
	if((v8 & 4) != 0) {
		return 0;
	}
	v9 = (float)x;
	v10 = (float)y;
	v11 = (float)z;
	if(v8 != 2 && v8) {
		this->aabb.minY = v10;
		this->aabb.minZ = v11;
		this->aabb.minX = v9 + 0.375;
		this->aabb.maxX = v9 + 0.625;
		v12 = v11 + 1.0;
		this->aabb.maxY = v10 + 1.5;
	} else {
		this->aabb.minX = v9;
		this->aabb.minY = v10;
		this->aabb.minZ = v11 + 0.375;
		this->aabb.maxX = v9 + 1.0;
		this->aabb.maxY = v10 + 1.5;
		v12 = v11 + 0.625;
	}
	this->aabb.maxZ = v12;
	return &this->aabb;
}
bool_t FenceGateTile::isSolidRender() {
	return 0;
}
bool_t FenceGateTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	if(level->getMaterial(x, y - 1, z)->isSolid()) {
		return Tile::mayPlace(level, x, y, z);
	}
	return 0;
}
bool_t FenceGateTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	int32_t data;	 // r0
	int32_t newdata; // r4
	float v11;	 // s15
	int32_t v12;	 // r3
	int32_t dir;	 // r3

	data = level->getData(x, y, z);
	if((data & 4) != 0) {
		newdata = data & ~4;
	} else {
		v11 = (float)((float)(player->yaw * 4.0) / 360.0) + 0.5;
		v12 = (int32_t)v11;
		if(v11 < (float)(int32_t)v11) {
			v12 = v12 - 1;
		}
		dir = v12 & 3;
		if((data & 3) == (((int8_t)dir + 2) & 3)) {
			data = dir;
		}
		newdata = data | 4;
	}
	level->setData(x, y, z, newdata, 2);
	level->levelEvent(player, 1003, x, y, z, 0);
	return 1;
}
int32_t FenceGateTile::getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t, float, float, float, Mob* pl, int32_t) {
	float v11 = (float)(pl->yaw * 4) / 360.0 + 0.5;
	int32_t v12 = (int32_t)v11;
	if(v11 < v12) v12 = v12 - 1;
	return v12 & 3;
}
