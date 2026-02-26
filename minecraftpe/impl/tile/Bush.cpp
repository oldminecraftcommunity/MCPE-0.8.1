#include <tile/Bush.hpp>
#include <tile/material/Material.hpp>
#include <level/Level.hpp>
Bush::Bush(int32_t a2, const std::string& a3, Material* mat)
	: Tile(a2, a3, mat) {
	this->setTicking(1);
	this->setShape(0.3, 0, 0.3, 0.7, 0.6, 0.7);
}
Bush::Bush(int32_t a2, const std::string& a3)
	: Bush(a2, a3, Material::plant){
}
bool_t Bush::checkAlive(Level* level, int32_t x, int32_t y, int32_t z) {
	if(!this->canSurvive(level, x, y, z)) {
		this->spawnResources(level, x, y, z, level->getData(x, y, z));
		return level->setTile(x, y, z, 0, 3);
	}
	return 1;
}
Bush::~Bush() {
}
bool_t Bush::isCubeShaped() {
	return 0;
}
int32_t Bush::getRenderShape() {
	return 1;
}
AABB* Bush::getAABB(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t Bush::isSolidRender() {
	return 0;
}
bool_t Bush::mayPlace(Level* level, int32_t x, int32_t y, int32_t z, uint8_t) {
	return this->mayPlaceOn(level->getTile(x, y - 1, z));
}
void Bush::tick(Level* a2, int32_t a3, int32_t a4, int32_t a5, Random*) {
	this->checkAlive(a2, a3, a4, a5);
}
void Bush::neighborChanged(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	Tile::neighborChanged(a2, a3, a4, a5, a6, a7, a8, a9);
	this->checkAlive(a2, a3, a4, a5);
}
int32_t Bush::getRenderLayer() {
	return 1;
}
bool_t Bush::canSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
	if(level->getRawBrightness(x, y, z) > 7 || level->canSeeSky(x, y, z)) {
		return this->mayPlaceOn(level->getTile(x, y - 1, z));
	}
	return 0;
}
bool_t Bush::mayPlaceOn(int32_t a2) {
	return a2 == Tile::grass->blockID || a2 == Tile::dirt->blockID || a2 == Tile::farmland->blockID;
}
