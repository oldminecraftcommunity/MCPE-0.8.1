#include <tile/FenceTile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

bool_t FenceTile::connectsTo(struct LevelSource* level, int32_t x, int32_t y, int32_t z){
	int32_t v6;	  // r0
	Tile* v7; // r4

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

FenceTile::FenceTile(int32_t id, const std::string& n, Material* m) : Tile(id, n, m){

}

FenceTile::~FenceTile() {
}
bool_t FenceTile::isCubeShaped() {
	return 0;
}
int32_t FenceTile::getRenderShape() {
	return 11;
}
void FenceTile::updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	bool_t zNeg; // r11
	bool_t zPos; // r10
	bool_t xNeg; // r9
	bool_t xPos; // r0
	float minZ;	 // r3
	float maxX;	 // s13
	float maxZ;	 // s11
	float minX;	 // r1

	zNeg = this->connectsTo(level, x, y, z - 1);
	zPos = this->connectsTo(level, x, y, z + 1);
	xNeg = this->connectsTo(level, x - 1, y, z);
	xPos = this->connectsTo(level, x + 1, y, z);
	if(zNeg) {
		minZ = 0.0;
	} else {
		minZ = 0.375;
	}
	maxX = 0.625;
	if(zPos) {
		maxZ = 1.0;
	} else {
		maxZ = 0.625;
	}
	if(xNeg) {
		minX = 0.0;
	} else {
		minX = 0.375;
	}
	if(xPos) {
		maxX = 1.0;
	}
	this->setShape(minX, 0.0, minZ, maxX, 1.0, maxZ);
}
AABB* FenceTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z){
	bool_t zNeg; // r11
	bool_t zPos; // r10
	bool_t xNeg; // r9
	bool_t xPos; // r0
	float minX;	 // s12
	float minZ;	 // s8
	float maxZ;	 // s10
	bool_t v16;	 // zf
	float maxX;	 // s9

	zNeg = this->connectsTo(level, x, y, z - 1);
	zPos = this->connectsTo(level, x, y, z + 1);
	xNeg = this->connectsTo(level, x - 1, y, z);
	xPos = this->connectsTo(level, x + 1, y, z);
	minX = 0.375;
	if(zNeg) {
		minZ = 0.0;
	} else {
		minZ = 0.375;
	}
	if(zPos) {
		maxZ = 1.0;
	} else {
		maxZ = 0.625;
	}
	if(xNeg) {
		minX = 0.0;
	}
	v16 = !xPos;
	if(v16) {
		maxX = 0.625;
	} else {
		maxX = 1.0;
	}
	this->aabb.minX = (float)x + minX;
	this->aabb.maxX = (float)x + maxX;
	this->aabb.minY = (float)y;
	this->aabb.minZ = (float)z + minZ;
	this->aabb.maxZ = (float)z + maxZ;
	this->aabb.maxY = (float)y + 1.5;
	return &this->aabb;
}
bool_t FenceTile::isSolidRender() {
	return 0;
}
bool_t FenceTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	return Tile::mayPlace(level, x, y, z);
}
