#include <tile/TopSnowTile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <entity/ItemEntity.hpp>
#include <level/LightLayer.hpp>

TopSnowTile::TopSnowTile(int32_t id, const std::string& name, Material* mat)
	: Tile(id, name, mat) {
	this->setShape(0, 0, 0, 1, 0.125, 1);
	this->setTicking(1);
	this->replaceable = 1;
	this->field_5C = 255;
}
bool_t TopSnowTile::checkCanSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v10; // r0

	if(this->mayPlace(level, x, y, z)) return 1;
	v10 = level->getData(x, y, z);
	this->spawnResources(level, x, y, z, v10);
	level->setTile(x, y, z, 0, 3);
	return 0;
}

TopSnowTile::~TopSnowTile() {
}
int32_t TopSnowTile::getTileType() {
	return 4;
}
bool_t TopSnowTile::isCubeShaped() {
	return 0;
}
bool_t TopSnowTile::shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t face) {
	Material* mat; // r0

	mat = level->getMaterial(x, y, z);
	if(face == 1) {
		return 1;
	}
	if(mat == this->material) {
		return 0;
	}
	return Tile::shouldRenderFace(level, x, y, z, face);
}
AABB* TopSnowTile::getAABB(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t TopSnowTile::isSolidRender() {
	return 0;
}
bool_t TopSnowTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t yb; // r6
	int32_t id; // r0
	Material* mat; // r0

	yb = y - 1;
	id = level->getTile(x, y - 1, z);
	if(!id || !Tile::tiles[id]->isSolidRender()) {
		return 0;
	}
	mat = level->getMaterial(x, yb, z);
	return mat->blocksMotion();
}
void TopSnowTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
	int32_t v11; // r0

	if(level->getBrightness(LightLayer::Block, x, y, z) > 11) {
		v11 = level->getData(x, y, z);
		this->spawnResources(level, x, y, z, v11);
		level->setTile(x, y, z, 0, 3);
	}
}
void TopSnowTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
	this->checkCanSurvive(level, x, y, z);
}
int32_t TopSnowTile::getResource(int32_t, Random*) {
	return Item::snowBall->itemID;
}
int32_t TopSnowTile::getResourceCount(Random*) {
	return 0;
}
float TopSnowTile::getThickness() {
	return 0.13;
}
void TopSnowTile::playerDestroy(Level* level, Player* player, int32_t x, int32_t y, int32_t z, int32_t a7) {
	Random* p_random; // r6
	int32_t itemID;		  // r9
	float f;		  // s18
	float f1;		  // s17
	float f2;		  // s16
	ItemEntity* v15;  // r6

	if(!level->isClientMaybe) {
		p_random = &level->random;
		itemID = Item::snowBall->itemID;
		f = p_random->nextFloat();
		f1 = p_random->nextFloat();
		f2 = p_random->nextFloat();
		v15 = new ItemEntity(level, (float)x + (float)((float)(f * 0.7) + 0.15), (float)y + (float)((float)(f1 * 0.7) + 0.15), (float)z + (float)((float)(f2 * 0.7) + 0.15), ItemInstance(itemID, 1, 0));
		v15->delayBeforePickup = 10;
		level->addEntity(v15);
		level->setTile(x, y, z, 0, 3);
	}
}
