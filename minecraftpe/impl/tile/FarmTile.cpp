#include <tile/FarmTile.hpp>
#include <tile/material/Material.hpp>
#include <level/Level.hpp>
#include <entity/Entity.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

FarmTile::FarmTile(int32_t id)
	: Tile(id, Material::dirt) {
	this->field_80 = this->getTextureUVCoordinateSet("dirt", 0);
	TextureAtlasTextureItem* ti = this->getTextureItem("farmland");
	this->textureUV = *ti->getUV(0);
	this->field_98 = this->textureUV;
	this->field_B0 = *ti->getUV(1);
	this->setTicking(1);
	this->setShape(0, 0, 0, 1, 0.9375, 1);
	this->setLightBlock(255);
}


FarmTile::~FarmTile() {
}
bool_t FarmTile::isCubeShaped() {
	return 0;
}
TextureUVCoordinateSet* FarmTile::getTexture(int32_t a2, int32_t a3) {
	if(a2 != 1) return &this->field_80;
	if(a3 <= 0) return &this->field_B0;
	return &this->field_98;
}
AABB* FarmTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->aabb.minX = x;
	this->aabb.minY = y;
	this->aabb.minZ = z;
	this->aabb.maxX = x + 1;
	this->aabb.maxY = y + 1;
	this->aabb.maxZ = z + 1;
	return &this->aabb;
}
bool_t FarmTile::isSolidRender() {
	return 0;
}
void FarmTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng){
	int32_t xx;		 // r10
	int32_t zz;		 // r11
	int32_t yy;		 // r9
	int32_t data;	 // r0
	int32_t newdata; // [sp+30h] [bp+0h]

	for(xx = x - 4; xx <= x + 4; ++xx) {
		yy = y;
LABEL_7:
		if(yy <= y + 1) {
			for(zz = z - 4;; ++zz) {
				if(zz > z + 4) {
					++yy;
					goto LABEL_7;
				}
				if(Material::water == level->getMaterial(xx, yy, zz)) {
					break;
				}
			}
			newdata = 7;
			goto LABEL_16;
		}
	}
	data = level->getData(x, y, z);
	if(data > 0) {
		newdata = data - 1;
LABEL_16:
		level->setData(x, y, z, newdata, 2);
		return;
	}
	if(level->getTile(x, y + 1, z) != Tile::crops->blockID) {
		level->setTile(x, y, z, Tile::dirt->blockID, 3);
	}
}
void FarmTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	Tile::neighborChanged(level, x, y, z, a6, a7, a8, a9);
	if(level->getMaterial(x, y + 1, z)->isSolid()) {
		level->setTile(x, y, z, Tile::dirt->blockID, 3);
	}
}
int32_t FarmTile::getResource(int32_t a2, Random* a3) {
	return Tile::dirt->getResource(0, a3);
}
void FarmTile::fallOn(Level* level, int32_t x, int32_t y, int32_t z, Entity* ent, float fd) {
	if(!level->isClientMaybe && level->random.nextFloat() < (fd - 0.5)) {
		level->setTile(x, y, z, Tile::dirt->blockID, 3);
	}
}
