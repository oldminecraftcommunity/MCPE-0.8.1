#include <level/chunk/EmptyLevelChunk.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
#include <string.h>

EmptyLevelChunk::EmptyLevelChunk(Level* level)
	: LevelChunk(level, 0, 0, 0) {
	this->field_24A = 1;
}
EmptyLevelChunk::~EmptyLevelChunk() {
}
bool_t EmptyLevelChunk::isAt(int32_t x, int32_t z) {
	return x == this->chunkX && z == this->chunkZ;
}
int32_t EmptyLevelChunk::getHeightmap(int32_t, int32_t) {
	return 0;
}
void EmptyLevelChunk::recalcHeightmap() {
}
void EmptyLevelChunk::recalcHeightmapOnly() {
}
int32_t EmptyLevelChunk::getBrightness(const struct LightLayer&, int32_t, int32_t, int32_t) {
	return 7;
}
void EmptyLevelChunk::setBrightness(const struct LightLayer&, int32_t, int32_t, int32_t, int32_t) {
}
int32_t EmptyLevelChunk::getRawBrightness(int32_t, int32_t, int32_t, int32_t) {
	return 7;
}
void EmptyLevelChunk::addEntity(struct Entity*) {
}
void EmptyLevelChunk::removeEntity(struct Entity*) {
}
void EmptyLevelChunk::removeEntity(struct Entity*, int32_t) {
}
bool_t EmptyLevelChunk::isSkyLit(int32_t, int32_t, int32_t) {
	return 0;
}
void EmptyLevelChunk::lightLava() {
}
void EmptyLevelChunk::recalcBlockLights() {
}
void EmptyLevelChunk::skyBrightnessChanged() {
}
void EmptyLevelChunk::load() {
}
void EmptyLevelChunk::unload() {
}
void EmptyLevelChunk::markUnsaved() {
}
void EmptyLevelChunk::getEntities(struct Entity*, const struct AABB&, std::vector<struct Entity*>&) {
}
int32_t EmptyLevelChunk::getTile(int32_t, int32_t, int32_t) {
	return Tile::invisible_bedrock->blockID;
}
bool_t EmptyLevelChunk::setTile(int32_t, int32_t, int32_t, int32_t) {
	return 1;
}
bool_t EmptyLevelChunk::setTileAndData(int32_t, int32_t, int32_t, int32_t, int32_t) {
	return 1;
}
int32_t EmptyLevelChunk::getData(int32_t, int32_t, int32_t) {
	return 0;
}
bool_t EmptyLevelChunk::setData(int32_t, int32_t, int32_t, int32_t) {
	return 0;
}
void EmptyLevelChunk::setBlocks(uint8_t*, int32_t) {
}
int32_t EmptyLevelChunk::getBlocksAndData(uint8_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	int32_t v9 = (a8 - a5) * (a6 - a3) * (a7 - a4);
	int32_t v10 = v9 + 3 * (v9 / 2);
	memset(&a2[a9], Tile::invisible_bedrock->blockID, v10);

	return v10;
}
int32_t EmptyLevelChunk::setBlocksAndData(uint8_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	int32_t v9 = (a8 - a5) * (a6 - a3) * (a7 - a4);
	return v9 + 3 * (v9 / 2);
}
Random EmptyLevelChunk::getRandom(int32_t a3){
	return Random(
		(this->level->getSeed()
		+ 4987142 * this->chunkX * this->chunkX
		+ 5947611 * this->chunkX
		+ 4392871 * this->chunkZ * this->chunkZ
		+ 389711 * this->chunkZ) ^ a3
	);
}
bool_t EmptyLevelChunk::isEmpty() {
	return 1;
}
