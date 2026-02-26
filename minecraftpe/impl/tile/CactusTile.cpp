#include <tile/CactusTile.hpp>
#include <entity/Entity.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

CactusTile::CactusTile(int32_t id)
	: Tile(id, Material::cactus) {
	TextureAtlasTextureItem* ti = this->getTextureItem("cactus");
	this->field_80 = *ti->getUV(0);
	this->field_98 = *ti->getUV(1);
	this->field_B0 = *ti->getUV(2);

	this->setTicking(1);
}

CactusTile::~CactusTile() {
}
bool_t CactusTile::isCubeShaped() {
	return 0;
}
int32_t CactusTile::getRenderShape() {
	return 13;
}
TextureUVCoordinateSet* CactusTile::getTexture(int32_t a2) {
	if(a2 == 1) return &this->field_80;
	if(a2) return &this->field_98;
	return &this->field_B0;
}

AABB* CactusTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->aabb.minX = x + 0.0625;
	this->aabb.minY = y;
	this->aabb.minZ = z + 0.0625;
	this->aabb.maxX = (x + 1) - 0.0625;
	this->aabb.maxY = (y + 1) - 0.0625;
	this->aabb.maxZ = (z + 1) - 0.0625;
	return &this->aabb;
}
AABB CactusTile::getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	return AABB{(float)x + 0.0625f, (float)y, (float)z + 0.0625f, (float)(x + 1) - 0.0625f, (float)y + 1.0f, (float)(z + 1) - 0.0625f};
}
bool_t CactusTile::isSolidRender() {
	return 0;
}
bool_t CactusTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	if(Tile::mayPlace(level, x, y, z)) {
		return this->canSurvive(level, x, y, z);
	}
	return 0;
}
void CactusTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* a6) {
	int32_t aboveY = y + 1;
	if(level->isEmptyTile(x, y + 1, z)) {
		int32_t i;
		for(i = 1; level->getTile(x, y - i, z) == this->blockID; ++i) {
		}
		if(i <= 2) {
			int32_t meta = level->getData(x, y, z);
			int32_t za;
			if(meta <= 9) za = meta + 1;
			else {
				level->setTile(x, aboveY, z, this->blockID, 3);
				za = 0;
			}
			level->setData(x, y, z, za, 4);
		}
	}
}
void CactusTile::neighborChanged(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	if(!this->canSurvive(a2, a3, a4, a5)) {
		this->spawnResources(a2, a3, a4, a5, a2->getData(a3, a4, a5), 1.0);
		a2->setTile(a3, a4, a5, 0, 3);
	}
}
int32_t CactusTile::getRenderLayer() {
	if(this->goodGraphics) return 3;
	return 1;
}
void CactusTile::entityInside(Level* level, int32_t x, int32_t y, int32_t z, Entity* ent) {
	ent->hurt(0, 1);
}
bool_t CactusTile::canSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
	if(level->getMaterial(x - 1, y, z)->isSolid()) return 0;
	if(level->getMaterial(x + 1, y, z)->isSolid()) return 0;
	if(level->getMaterial(x, y, z - 1)->isSolid()) return 0;
	if(level->getMaterial(x, y, z + 1)->isSolid()) return 0;
	int32_t bid = level->getTile(x, y - 1, z);
	return bid == Tile::cactus->blockID || bid == Tile::sand->blockID;
}
