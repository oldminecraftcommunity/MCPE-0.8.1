#include <tile/DoorTile.hpp>
#include <entity/Player.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

DoorTile::DoorTile(int32_t id, const Material* mat)
	: Tile(id, mat) {
	TextureAtlasTextureItem texItem(*this->getTextureItem("door"));
	this->field_80 = *texItem.getUV(1);
	this->field_98 = *texItem.getUV(0);
	this->field_B0 = *texItem.getUV(3);
	this->field_C8 = *texItem.getUV(2);
	if(mat != Material::metal) {
		this->textureUV = this->field_80;
	} else {
		this->textureUV = this->field_B0;
	}
	this->setShape(0, 0, 0, 1, 1, 1);
}
bool_t DoorTile::blocksLight() {
	return 0;
}
int32_t DoorTile::getCompositeData(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	uint32_t data; // r0
	int32_t v10;   // r6
	int8_t v11;	   // r5
	int8_t v12;	   // r0
	int8_t v13;	   // r3
	int32_t v14;   // r0
	int32_t v15;   // r3

	data = level->getData(x, y, z);
	v10 = (data >> 3) & 1;
	v11 = data;
	if(v10) {
		v12 = level->getData(x, y - 1, z);
		v13 = v11;
	} else {
		v13 = level->getData(x, y + 1, z);
		v12 = v11;
	}
	v14 = v12 & 7 | (8 * v10);
	if((v13 & 1) != 0) {
		v15 = 16;
	} else {
		v15 = 0;
	}
	return v14 | v15;
}
int32_t DoorTile::getDir(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	return DoorTile::getCompositeData(level, x, y, z) & 3;
}
bool_t DoorTile::isOpen(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	return ((uint32_t)DoorTile::getCompositeData(level, x, y, z) >> 2) & 1;
}
void DoorTile::setOpen(Level* level, int32_t x, int32_t y, int32_t z, bool_t open) {
	uint32_t CompositeData; // r0

	CompositeData = DoorTile::getCompositeData((LevelSource*)level, x, y, z);
	if(((CompositeData >> 2) & 1) != open) {
		if((CompositeData & 8) != 0) {
			level->setData(x, y - 1, z, CompositeData & 7 ^ 4, 2);
			level->setTilesDirty(x, y - 1, z, x, y, z);
		} else {
			level->setData(x, y, z, CompositeData & 7 ^ 4, 2);
			level->setTilesDirty(x, y, z, x, y, z);
		}
		level->levelEvent(0, 1003, x, y, z, 0);
	}
}

DoorTile::~DoorTile() {
}
bool_t DoorTile::isCubeShaped() {
	return 0;
}
int32_t DoorTile::getRenderShape() {
	return 7;
}
void DoorTile::updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	uint32_t cdata; // r6
	int32_t v7;		// r2
	int32_t v8;		// r3
	int32_t v9;		// r6
	Tile* tile;		// r0
	float minZ;		// r3
	float maxX;		// [sp+0h] [bp-20h]
	float maxZ;		// [sp+8h] [bp-18h]

	cdata = DoorTile::getCompositeData(level, x, y, z);
	this->setShape(0.0, 0.0, 0.0, 1.0, 2.0, 1.0);
	v7 = (cdata >> 2) & 1;
	v8 = (cdata >> 4) & 1;
	v9 = cdata & 3;
	switch(v9) {
		case 0:
			if(v7) {
				maxX = 1.0;
				if(!v8) {
					break;
				}
SET_MINZ_MAXZ:
				minZ = 0.8125;
				tile = (Tile*)this;
				maxZ = 1.0;
				goto SET_SHAPE_0_0_MINZ_MAXX_1_MAXZ;
			}
			goto SET_MAXX_MAXZ_MINZ;
		case 1:
			if(v7) {
				if(v8) {
					goto SET_MAXX_MAXZ_MINZ;
				}
				goto SET_SHAPE_STATIC;
			}
			maxX = 1.0;
			break;
		case 2:
			maxX = 1.0;
			if(!v7) {
				goto SET_SHAPE_STATIC;
			}
			if(!v8) {
				goto SET_MINZ_MAXZ;
			}
			break;
		default:
			if(!v7) {
				maxX = 1.0;
				goto SET_MINZ_MAXZ;
			}
			if(!v8) {
SET_MAXX_MAXZ_MINZ:
				maxX = 0.1875;
				maxZ = 1.0;
				goto SET_MINZ_0;
			}
SET_SHAPE_STATIC:
			this->setShape(0.8125, 0.0, 0.0, 1.0, 1.0, 1.0);
			return;
	}
	maxZ = 0.1875;
SET_MINZ_0:
	tile = (Tile*)this;
	minZ = 0.0;
SET_SHAPE_0_0_MINZ_MAXX_1_MAXZ:
	this->setShape(0.0, 0.0, minZ, maxX, 1.0, maxZ);
}
TextureUVCoordinateSet* DoorTile::getTexture(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	int8_t cdata;				 // r0
	const Material* material;	 // r3
	int8_t v9;					 // r12
	TextureUVCoordinateSet* v10; // r7
	float minX;					 // r0
	float minY;					 // r1
	float maxX;					 // r2
	float maxY;					 // r3
	int32_t v16;				 // r3
	bool_t v17;					 // zf
	bool_t v18;					 // zf
	float v19;					 // r2
	float v21;					 // [sp+0h] [bp-30h]
	float v22;					 // [sp+8h] [bp-28h]
	float v23;					 // [sp+Ch] [bp-24h]
	float v24;					 // [sp+10h] [bp-20h]
	float v25;					 // [sp+14h] [bp-1Ch]

	if((uint32_t)a6 > 1) {
		cdata = DoorTile::getCompositeData(level, x, y, z);
		material = this->material;
		v9 = cdata;
		if((cdata & 8) != 0) {
			if(material == Material::metal) {
				v10 = &this->field_B0;
			} else {
				v10 = &this->field_80;
			}
		} else if(material == Material::metal) {
			v10 = &this->field_C8;
		} else {
			v10 = &this->field_98;
		}
		minX = v10->minX;
		minY = v10->minY;
		maxX = v10->maxX;
		maxY = v10->maxY;
		v21 = minX;
		v22 = maxX;
		v23 = maxY;
		v16 = v9 & 3;
		v24 = v10->width;
		v25 = v10->height;
		if((v9 & 4) != 0) {
			if((v9 & 3) != 0) {
				if(v16 == 1) {
					v17 = a6 == 5;
				} else if(v16 == 2) {
					v17 = a6 == 3;
				} else {
					v17 = a6 == 4;
				}
			} else {
				v17 = a6 == 2;
			}
			if(!v17) {
				goto LABEL_32;
			}
		} else {
			if((v9 & 3) != 0) {
				if(v16 == 1) {
					v18 = a6 == 3;
				} else if(v16 == 2) {
					v18 = a6 == 4;
				} else {
					v18 = a6 == 2;
				}
			} else {
				v18 = a6 == 5;
			}
			if(v18) {
				v22 = minX;
				v21 = maxX;
			}
			if((v9 & 0x10) == 0) {
				goto LABEL_32;
			}
		}
		v19 = v22;
		v22 = v21;
		v21 = v19;
LABEL_32:
		this->textureUV.minX = v21;
		this->textureUV.minY = minY;
		this->textureUV.maxX = v22;
		this->textureUV.maxY = v23;
		this->textureUV.width = v24;
		this->textureUV.height = v25;
	}
	return &this->textureUV;
}
AABB* DoorTile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->updateShape(level, x, y, z);
	return Tile::getAABB(level, x, y, z);
}
AABB DoorTile::getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->updateShape(level, x, y, z);
	return Tile::getTileAABB(level, x, y, z);
}
bool_t DoorTile::isSolidRender() {
	return 0;
}
bool_t DoorTile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	return y <= 126 && level->isSolidBlockingTile(x, y - 1, z) && Tile::mayPlace(level, x, y, z) && Tile::mayPlace(level, x, y + 1, z);
}
void DoorTile::playerWillDestroy(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, Player* player) {
	if(player->abilities.instabuild) {
		if((a6 & 8) != 0) {
			int32_t v9 = y - 1;
			if(level->getTile(x, v9, z) == this->blockID) {
				level->removeTile(x, v9, z);
			}
		}
	}
}
void DoorTile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t xx, int32_t yy, int32_t zz, int32_t a9) {
	int32_t v13; // r0
	int32_t v15; // r12
	bool_t v16;	 // r3
	int32_t v17; // [sp+1Ch] [bp-3Ch]
	int32_t v18; // [sp+20h] [bp-38h]

	v13 = level->getData(x, y, z);
	v18 = v13;
	if((v13 & 8) != 0) {
		if(level->getTile(x, y - 1, z) != this->blockID) {
			level->setTile(x, y, z, 0, 3);
		}
		if(a9 > 0 && a9 != this->blockID) {
			this->neighborChanged(level, x, y - 1, z, xx, yy, zz, a9);
		}
	} else {
		if(level->getTile(x, y + 1, z) == this->blockID) {
			v15 = 0;
		} else {
			level->setTile(x, y, z, 0, 3);
			v15 = 1;
		}
		v17 = v15;
		if(!level->isSolidBlockingTile(x, y - 1, z)) {
			level->setTile(x, y, z, 0, 3);
			if(level->getTile(x, y + 1, z) == this->blockID) {
				level->setTile(x, y + 1, z, 0, 3);
			}
			goto LABEL_9;
		}
		if(v17) {
LABEL_9:
			if(!level->isClientMaybe) {
				this->spawnResources(level, x, y, z, v18, 1.0);
			}
			return;
		}
		if(level->hasNeighborSignal(x, y, z) || level->hasNeighborSignal(x, y + 1, z)) {
			v16 = 1;
		} else {
			if(a9 > 0) {
				if(!Tile::tiles[a9]->isSignalSource()) {
					return;
				}
			} else if(a9) {
				return;
			}
			v16 = 0;
		}
		if(a9 != this->blockID) {
			this->setOpen(level, x, y, z, v16);
		}
	}
}
int32_t DoorTile::getResource(int32_t a2, Random*) {
	if((a2 & 8) != 0) return 0;
	if(this->material == Material::metal) return Item::door_iron->itemID;
	return Item::door_wood->itemID;
}
HitResult DoorTile::clip(Level* level, int32_t x, int32_t y, int32_t z, const Vec3& v1, const Vec3& v2) {
	this->updateShape(level, x, y, z);
	return Tile::clip(level, x, y, z, v1, v2);
}
int32_t DoorTile::getRenderLayer() {
	return 1;
}
bool_t DoorTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	int8_t cdata; // r0

	if(this->material != Material::metal) {
		cdata = DoorTile::getCompositeData(level, x, y, z);
		if((cdata & 8) != 0) {
			level->setData(x, y - 1, z, cdata & 7 ^ 4, 2);
			level->setTilesDirty(x, y - 1, z, x, y, z);
		} else {
			level->setData(x, y, z, cdata & 7 ^ 4, 2);
			level->setTilesDirty(x, y, z, x, y, z);
		}
		level->levelEvent(player, 1003, x, y, z, 0);
	}
	return 1;
}
void DoorTile::attack(Level* a2, int32_t a3, int32_t a4, int32_t a5, Player* a6) {
	this->use(a2, a3, a4, a5, a6);
}
