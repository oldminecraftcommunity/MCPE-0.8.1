#include <tile/WallTile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

WallTile::WallTile(int32_t id, Tile* a3)
	: Tile(id, a3->material) {
	this->setDestroyTime(a3->blockResistance / 3.0);
	this->setSoundType(*a3->soundType);
}
bool_t WallTile::connectsTo(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t v6; // r0
	Tile* v7;	// r4

	v6 = level->getTile(x, y, z);
	if(v6 == this->blockID || v6 == Tile::fenceGate->blockID) {
		return 1;
	}
	v7 = Tile::tiles[v6];
	if(!v7) {
		return 0;
	}
	if(v7->material->isSolidBlocking() && v7->isCubeShaped()) {
		return v7->material != Material::vegetable;
	}
	return 0;
}

WallTile::~WallTile() {
}
bool_t WallTile::isCubeShaped() {
	return 0;
}
int32_t WallTile::getRenderShape() {
	return 32;
}
void WallTile::updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	bool_t zNeg; // r11
	bool_t zPos; // r10
	bool_t xNeg; // r9
	bool_t xPos; // r0
	float minX; // s13
	float maxY; // s15
	float maxX; // s11
	float minZ; // s14
	float maxZ; // s12

	zNeg = this->connectsTo(level, x, y, z - 1);
	zPos = this->connectsTo(level, x, y, z + 1);
	xNeg = this->connectsTo(level, x - 1, y, z);
	xPos = this->connectsTo(level, x + 1, y, z);
	minX = 0.25;
	maxY = 1.0;
	maxX = 0.75;
	if(zNeg) {
		minZ = 0.0;
	} else {
		minZ = 0.25;
	}
	if(zPos) {
		maxZ = 1.0;
	} else {
		maxZ = 0.75;
	}
	if(xNeg) {
		minX = 0.0;
	}
	if(xPos) {
		maxX = 1.0;
	}
	if(zNeg) {
		if(zPos && !xNeg) {
			if(!xPos) {
				maxY = 0.8125;
			}
			if(!xPos) {
				maxX = 0.6875;
			}
			if(!xPos) {
				minX = 0.3125;
			}
		}
	} else if(!zPos && xNeg) {
		if(xPos) {
			maxY = 0.8125;
		}
		if(xPos) {
			maxZ = 0.6875;
		}
		if(xPos) {
			minZ = 0.3125;
		}
	}
	this->setShape(minX, 0.0, minZ, maxX, maxY, maxZ);
}
bool_t WallTile::shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	return a6 || Tile::shouldRenderFace(level, x, y, z, 0);
}
TextureUVCoordinateSet* WallTile::getTexture(int32_t a2, int32_t a3) {
	if(a3 == 1) return Tile::mossStone->getTexture(a2);
	return Tile::stoneBrick->getTexture(a2);
}
AABB* WallTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->updateShape(level, x, y, z);
	this->maxY = 1.5;
	return Tile::getAABB(level, x, y, z);
}
bool_t WallTile::isSolidRender() {
	return 0;
}
int32_t WallTile::getSpawnResourcesAuxValue(int32_t a2) {
	return a2;
}
