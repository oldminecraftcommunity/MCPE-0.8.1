#pragma once
#include <tile/Tile.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <math/Mth.hpp>

struct FenceGateTile : Tile{
	FenceGateTile(int32_t id, const std::string& n, Material* mat) :
			Tile(id, n, mat) {
	}
	virtual ~FenceGateTile() {
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return 21;
	}
	virtual AABB* getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t v8; // r0
		float v9; // s13
		float v10; // s14
		float v11; // s15
		float v12; // s15
		v8 = level->getData(x, y, z);
		if ((v8 & 4) != 0) {
			return 0;
		}
		v9 = (float) (x);
		v10 = (float) (y);
		v11 = (float) (z);
		if (v8 != 2 && v8) {
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
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
		if (level->getMaterial(x, y - 1, z)->isSolid()) {
			return Tile::mayPlace(level, x, y, z);
		}
		return 0;
	}
	virtual bool_t use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
		int32_t data; // r0
		int32_t newdata; // r4
		float v11; // s15
		int32_t v12; // r3
		int32_t dir; // r3
		data = level->getData(x, y, z);
		if ((data & 4) != 0) {
			newdata = data & ~4;
		} else {
			v11 = (float) (((float) ((player->yaw * 4.0)) / 360.0)) + 0.5;
			v12 = (int32_t) (v11);
			if (v11 < (float) ((int32_t) (v11))) {
				v12 = v12 - 1;
			}
			dir = v12 & 3;
			if ((data & 3) == (((int8_t) (dir) + 2) & 3)) {
				data = dir;
			}
			newdata = data | 4;
		}
		level->setData(x, y, z, newdata, 2);
		level->levelEvent(player, 1003, x, y, z, 0);
		return 1;
	}
	virtual int32_t getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t, float, float, float, Mob* pl, int32_t) {
		return Mth::floor(((pl->yaw * 4)) / 360.0f + 0.5f) & 3;
	}
};
