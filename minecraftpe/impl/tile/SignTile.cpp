#include <tile/SignTile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

SignTile::SignTile(int32_t id, bool_t a3)
	: EntityTile(id, Material::wood) {
	this->field_80 = a3;
	this->textureUV = this->getTextureUVCoordinateSet("planks", 0);
	this->setShape(0.25, 0.0, 0.25, 0.75, 1.0, 0.75);
}

SignTile::~SignTile() {
}
bool_t SignTile::isCubeShaped() {
	return 0;
}
int32_t SignTile::getRenderShape() {
	return -1;
}
void SignTile::updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	int32_t v6;
	if(!this->field_80) {
		v6 = level->getData(x, y, z);
		this->setShape(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
		switch(v6) {
			case 2:
				this->setShape(0.0, 0.28125, 0.875, 1.0, 0.78125, 1.0);
				break;
			case 3:
				this->setShape(0.0, 0.28125, 0.0, 1.0, 0.78125, 0.125);
				break;
			case 4:
				this->setShape(0.875, 0.28125, 0.0, 1.0, 0.78125, 1.0);
				break;
			case 5:
				this->setShape(0.0, 0.28125, 0.0, 0.125, 0.78125, 1.0);
				break;
		}
	}
}
AABB* SignTile::getAABB(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
AABB SignTile::getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->updateShape(level, x, y, z);
	return Tile::getTileAABB(level, x, y, z);
}
bool_t SignTile::isSolidRender() {
	return 0;
}
bool_t SignTile::isPathfindable(LevelSource*, int32_t, int32_t, int32_t) {
	return 1;
}
int32_t SignTile::getTileEntityType() {
	return 4;
}
void SignTile::neighborChanged(Level* a2, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
	int32_t v16;   // r1
	int32_t v17;   // r2
	int32_t v18;   // r0
	Material* v20; // r0
	int32_t v22;   // r0

	if(this->field_80) {
		v16 = x;
		v17 = y - 1;
LABEL_8:
		v20 = a2->getMaterial(v16, v17, z);
		goto LABEL_9;
	}
	v18 = a2->getData(x, y, z);
	if(v18 == 2) {
		v20 = a2->getMaterial(x, y, z + 1);
		goto LABEL_9;
	}
	if(v18 != 3) {
		if(v18 == 4) {
			v16 = x + 1;
		} else {
			if(v18 != 5) {
				goto LABEL_10;
			}
			v16 = x - 1;
		}
		v17 = y;
		goto LABEL_8;
	}
	v20 = a2->getMaterial(x, y, z - 1);
LABEL_9:
	if(!v20->isSolid()) {
LABEL_10:
		v22 = a2->getData(x, y, z);
		this->spawnResources(a2, x, y, z, v22, 1.0);
		a2->setTile(x, y, z, 0, 3);
	}
	Tile::neighborChanged(a2, x, y, z, a6, a7, a8, a9);
}
int32_t SignTile::getResource(int32_t, Random*) {
	return Item::sign->itemID;
}
