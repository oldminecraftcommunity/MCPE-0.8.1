#include <tile/WoolCarpetTile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

WoolCarpetTile::WoolCarpetTile(int32_t a2)
	: Tile(a2, Material::cloth) {
	this->setShape(0.0, 0.0, 0.0, 1.0, 0.0625, 1.0);
	this->setTicking(1);
	this->updateShape(0);
}
bool_t WoolCarpetTile::checkCanSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
	if(this->canSurvive(level, x, y, z)) return 1;

	this->spawnResources(level, x, y, z, level->getData(x, y, z), 0);
	level->removeTile(x, y, z);
	return 0;
}
int32_t WoolCarpetTile::getItemAuxValueForTileData(int32_t a1) {
	return ~(int8_t)a1 & 0xF;
}
int32_t WoolCarpetTile::getTileDataForItemAuxValue(int32_t a1) {
	return ~(int8_t)a1 & 0xF;
}
void WoolCarpetTile::updateDefaultShape() {
	this->updateShape(0);
}

WoolCarpetTile::~WoolCarpetTile() {
}
bool_t WoolCarpetTile::isCubeShaped() {
	return 0;
}
void WoolCarpetTile::updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	this->updateShape(level->getData(x, y, z));
}
void WoolCarpetTile::updateShape(int32_t a2) {
	this->setShape(0.0, 0.0, 0.0, 1.0, 0.0625, 1.0);
}
bool_t WoolCarpetTile::shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t side) {
	if(side == 1) {
		return 1;
	} else {
		return Tile::shouldRenderFace(level, x, y, z, side);
	}
}
TextureUVCoordinateSet* WoolCarpetTile::getTexture(int32_t a2, int32_t a3) {
	return Tile::cloth->getTexture(a2, a3);
}
AABB* WoolCarpetTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	float maxZ; // s9
	float minY; // s10
	float v7;	// s12
	float v8;	// s13
	float minX; // s9

	maxZ = this->maxZ;
	minY = this->minY;
	v7 = (float)x + this->maxX;
	this->aabb.minZ = (float)z + this->minZ;
	v8 = (float)z + maxZ;
	minX = this->minX;
	this->aabb.maxX = v7;
	this->aabb.maxZ = v8;
	this->aabb.minX = (float)x + minX;
	this->aabb.minY = (float)y + minY;
	this->aabb.maxY = (float)y + 0.0;
	return &this->aabb;
}
bool_t WoolCarpetTile::isSolidRender() {
	return 0;
}
bool_t WoolCarpetTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	if(Tile::mayPlace(level, x, y, z)) {
		return this->canSurvive(level, x, y, z);
	}
	return 0;
}
void WoolCarpetTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
	this->checkCanSurvive(level, x, y, z);
}
float WoolCarpetTile::getThickness() {
	return 0.07;
}
bool_t WoolCarpetTile::canSurvive(Level* level, int32_t x, int32_t y, int32_t z){
	return !level->isEmptyTile(x, y - 1, z);
}
int32_t WoolCarpetTile::getSpawnResourcesAuxValue(int32_t a2) {
	return a2;
}
