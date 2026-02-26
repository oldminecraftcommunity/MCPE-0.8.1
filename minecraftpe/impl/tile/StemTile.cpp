#include <tile/StemTile.hpp>
#include <level/Level.hpp>
#include <utils.h>
#include <item/Item.hpp>
#include <item/ItemInstance.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

StemTile::StemTile(int32_t a2, Tile* a3)
	: Bush(a2, "melon_stem", Material::plant) {
	this->grownTile = a3;
	this->setTicking(1);
	this->setShape(0.375, 0.0, 0.375, 0.625, 0.25, 0.625);
	TextureAtlasTextureItem* texItem = this->getTextureItem(a3 == Tile::melon ? "melon_stem" : "pumpkin_stem");
	this->field_84 = *texItem->getUV(1);
	this->field_9C = *texItem->getUV(0);
}

int32_t StemTile::getConnectDir(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	if(level->getData(x, y, z) <= 6) {
		return -1;
	}
	if(level->getData(x - 1, y, z) == this->grownTile->blockID) {
		return 0;
	}
	if(level->getData(x + 1, y, z) == this->grownTile->blockID) {
		return 1;
	}
	if(level->getData(x, y, z - 1) == this->grownTile->blockID) {
		return 2;
	}
	if(level->getData(x, y, z + 1) == this->grownTile->blockID) {
		return 3;
	}
	return -1;
}
TextureUVCoordinateSet* StemTile::getConnectedTexture() {
	return &this->field_84;
}
float StemTile::getGrowthSpeed(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v8;		 // r5
	int32_t v9;		 // r8
	int32_t v10;	 // r6
	int32_t v11;	 // r0
	int32_t blockID; // r3
	bool_t v13;		 // r2
	bool_t v14;		 // r2
	bool_t v15;		 // r8
	float v16;		 // s16
	int32_t v17;	 // r11
	float v18;		 // s15
	int32_t i;		 // r6
	int32_t v21;	 // [sp+4h] [bp-54h]
	bool_t v22;		 // [sp+4h] [bp-54h]
	int32_t v23;	 // [sp+8h] [bp-50h]
	bool_t v24;		 // [sp+8h] [bp-50h]
	int32_t v25;	 // [sp+10h] [bp-48h]
	int32_t v26;	 // [sp+14h] [bp-44h]
	int32_t v27;	 // [sp+18h] [bp-40h]

	v23 = level->getTile(x, y, z - 1);
	v8 = x - 1;
	v25 = level->getTile(x, y, z + 1);
	v21 = level->getTile(x - 1, y, z);
	v26 = level->getTile(x + 1, y, z);
	v27 = level->getTile(x - 1, y, z - 1);
	v9 = level->getTile(x + 1, y, z - 1);
	v10 = level->getTile(x + 1, y, z + 1);
	v11 = level->getTile(x - 1, y, z + 1);
	blockID = this->blockID;
	v13 = v21 == blockID || v26 == blockID;
	v22 = v13;
	v14 = v23 == blockID || v25 == blockID;
	v24 = v14;
	v15 = v27 == blockID || v9 == blockID || v10 == blockID || v11 == blockID;
	v16 = 1.0;
	v17 = y - 1;
	while(v8 <= x + 1) {
		for(i = z - 1; i <= z + 1; ++i) {
			if(level->getTile(v8, v17, i) == Tile::farmland->blockID) {
				if(level->getData(v8, v17, i) > 0) {
					v18 = 3.0;
				} else {
					v18 = 1.0;
				}
			} else {
				v18 = 0.0;
			}
			if(v8 != x || i != z) {
				v18 = v18 * 0.25;
			}
			v16 = v16 + v18;
		}
		++v8;
	}
	if(v15 || v22 && v24) {
		return v16 * 0.5;
	}
	return v16;
}

StemTile::~StemTile() {
}
bool_t StemTile::onFertilized(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v8; // r8
	int32_t v9; // r3

	v8 = level->getData(x, y, z);
	v9 = level->random.genrand_int32() % 3 + v8 + 2;
	if(v9 >= 7) {
		v9 = 7;
	}
	level->setData(x, y, z, v9, 2);
	return 1;
}
int32_t StemTile::getRenderShape() {
	return 19;
}
void StemTile::updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z){
	int32_t v6;				 // r0
	float v8;			 // s15

	v6 = level->getData(x, y, z);
	v8 = vcvts_n_f32_s32(2 * (v6 + 1), 4u);
	this->maxY = v8;
	this->setShape(0.375, 0.0, 0.375, 0.625, v8, 0.625);
}
void StemTile::updateDefaultShape() {
	this->setShape(0.375, 0.0, 0.375, 0.625, 0.25, 0.625);
}
TextureUVCoordinateSet* StemTile::getTexture(int32_t, int32_t) {
	return &this->field_9C;
}
void StemTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	float growthSpeed; // s16
	uint32_t v10;	   // r8
	int32_t v11;	   // r0
	int32_t v12;	   // r10
	int32_t v13;	   // r9
	int32_t v15;	   // [sp+10h] [bp-50h]

	this->checkAlive(level, x, y, z);
	if(level->getRawBrightness(x, y + 1, z) > 8) {
		growthSpeed = this->getGrowthSpeed(level, x, y, z);
		v10 = rng->genrand_int32() % ((int32_t)(float)(25.0 / growthSpeed) + 1);
		if(!v10) {
			v11 = level->getData(x, y, z);
			if(v11 <= 6) {
				level->setData(x, y, z, v11 + 1, 2);
				return;
			}
			if(level->getTile(x - 1, y, z) != this->grownTile->blockID && level->getTile(x + 1, y, z) != this->grownTile->blockID && level->getTile(x, y, z - 1) != this->grownTile->blockID && level->getTile(x, y, z + 1) != this->grownTile->blockID) {
				while(v10) {
					if(v10 == 1) {
						v12 = x + 1;
						goto LABEL_17;
					}
					v12 = x;
					if(v10 == 2) {
						v13 = z - 1;
					} else {
						if(v10 != 3) {
							goto LABEL_17;
						}
						v13 = z + 1;
					}
LABEL_18:
					v15 = level->getTile(v12, y - 1, v13);
					if(!level->getTile(v12, y, v13) && (v15 == Tile::farmland->blockID || v15 == Tile::dirt->blockID || v15 == Tile::grass->blockID)) {
						level->setTile(v12, y, v13, this->grownTile->blockID, 3);
						return;
					}
					if(++v10 == 4) {
						return;
					}
				}
				v12 = x - 1;
LABEL_17:
				v13 = z;
				goto LABEL_18;
			}
		}
	}
}
int32_t StemTile::getResource(int32_t, Random*) {
	return -1;
}
int32_t StemTile::getResourceCount(Random*) {
	return 1;
}
void StemTile::spawnResources(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, float a7) {
	Item* v11;		  // r3
	int32_t v12;	  // r4
	ItemInstance v14; // [sp+14h] [bp-3Ch] BYREF

	this->spawnResources(level, x, y, z, a6, a7);
	if(!level->isClientMaybe) {
		if(this->grownTile == Tile::melon) {
			v11 = Item::seeds_melon;
		} else {
			v11 = Item::seeds_pumpkin;
		}
		v12 = 3;
		do {
			if((int32_t)(level->random.genrand_int32() % 0xF) <= a6) {
				this->popResource(level, x, y, z, ItemInstance(v11));
			}
			--v12;
		} while(v12);
	}
}
int32_t StemTile::getColor(int32_t a2) {
	return (4 * a2) | (a2 << 21) | ((255 - 8 * a2) << 8);
}
int32_t StemTile::getColor(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	return this->getColor(level->getData(x, y, z));
}
bool_t StemTile::mayPlaceOn(int32_t a2) {
	return a2 == Tile::farmland->blockID;
}
