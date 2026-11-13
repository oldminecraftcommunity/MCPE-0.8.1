#pragma once
#include <tile/Tile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

struct FenceTile : Tile{
	bool_t connectsTo(struct LevelSource* level, int32_t x, int32_t y, int32_t z) {
		int32_t v6; // r0
		Tile* v7; // r4
		v6 = level->getTile(x, y, z);
		if (v6 == this->blockID || v6 == Tile::fenceGate->blockID) {
			return 1;
		}
		v7 = Tile::tiles[v6];
		if (!v7) {
			return 0;
		}
		if (v7->material->isSolidBlocking() && v7->isCubeShaped()) {
			return v7->material != Material::vegetable;
		}
		return 0;
	}

	FenceTile(int32_t id, const std::string& n, Material* m) :
			Tile(id, n, m) {
	}

	virtual ~FenceTile() {
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return 11;
	}
	virtual void updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
		bool_t zNeg; // r11
		bool_t zPos; // r10
		bool_t xNeg; // r9
		bool_t xPos; // r0
		float minZ; // r3
		float maxX; // s13
		float maxZ; // s11
		float minX; // r1
		zNeg = this->connectsTo(level, x, y, z - 1);
		zPos = this->connectsTo(level, x, y, z + 1);
		xNeg = this->connectsTo(level, x - 1, y, z);
		xPos = this->connectsTo(level, x + 1, y, z);
		if (zNeg) {
			minZ = 0.0;
		} else {
			minZ = 0.375;
		}
		maxX = 0.625;
		if (zPos) {
			maxZ = 1.0;
		} else {
			maxZ = 0.625;
		}
		if (xNeg) {
			minX = 0.0;
		} else {
			minX = 0.375;
		}
		if (xPos) {
			maxX = 1.0;
		}
		this->setShape(minX, 0.0, minZ, maxX, 1.0, maxZ);
	}
	virtual AABB* getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
		bool zNeg = this->connectsTo(level, x, y, z - 1);
		bool zPos = this->connectsTo(level, x, y, z + 1);
		bool xNeg = this->connectsTo(level, x - 1, y, z);
		bool xPos = this->connectsTo(level, x + 1, y, z);

		float minX = 0.375f;
		float minZ = 0.375f;
		float maxX = 0.625f;
		float maxZ = 0.625f;

		if (zNeg) {
			minZ = 0.0;
		}
		if (zPos) {
			maxZ = 1.0;
		}
		if (xNeg) {
			minX = 0.0;
		}
		if (xPos) {
			maxX = 1.0;
		}

		this->aabb.minX = x + minX;
		this->aabb.maxX = x + maxX;
		this->aabb.minY = y;
		this->aabb.minZ = z + minZ;
		this->aabb.maxZ = z + maxZ;
		this->aabb.maxY = y + 1.5f;
		return &this->aabb;
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
		return Tile::mayPlace(level, x, y, z);
	}
};
