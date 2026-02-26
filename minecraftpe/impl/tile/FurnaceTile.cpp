#include <tile/FurnaceTile.hpp>
#include <level/Level.hpp>
#include <tile/entity/FurnaceTileEntity.hpp>
#include <entity/ItemEntity.hpp>
#include <tile/entity/FurnaceTileEntity.hpp>
#include <entity/Player.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

bool_t FurnaceTile::noDrop = 0;

FurnaceTile::FurnaceTile(int32_t a2, bool_t a3)
	: EntityTile(a2, Material::stone) {
	this->isLit = a3;
	TextureAtlasTextureItem* texItem = this->getTextureItem("furnace");

	this->field_A50 = *texItem->getUV(0);
	this->field_A68 = *texItem->getUV(1);
	this->field_A80 = *texItem->getUV(2);
	this->field_A98 = *texItem->getUV(3);

	this->textureUV = this->field_A50;
}
void FurnaceTile::setLit(bool_t a1, Level* level, int32_t x, int32_t y, int32_t z) {
	TileEntity* TileEntity; // r0
	FurnaceTileEntity* v10; // r8
	Tile* v11;				// r3
	int32_t v12;				// [sp+Ch] [bp-2Ch]

	v12 = level->getData(x, y, z);
	TileEntity = level->getTileEntity(x, y, z);
	v10 = (FurnaceTileEntity*)TileEntity;
	if(TileEntity) {
		if(TileEntity->isType(1)) {
			v10->field_64 = 1;
			FurnaceTile::noDrop = 1;
			if(a1) {
				v11 = Tile::furnace_lit;
			} else {
				v11 = Tile::furnace;
			}
			level->setTile(x, y, z, v11->blockID, 2);
			FurnaceTile::noDrop = 0;
			v10->field_64 = 0;
			level->setData(x, y, z, v12, 2);
		}
	}
}

FurnaceTile::~FurnaceTile() {
}
TextureUVCoordinateSet* FurnaceTile::getTexture(int32_t a2) {
	if(a2 == 1 || a2 == 0) {
		return &this->field_A98;
	}
	if(a2 == 3) return &this->field_A50;
	return &this->field_A80;
}
TextureUVCoordinateSet* FurnaceTile::getTexture(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	if((uint32_t)a6 <= 1) {
		return &this->field_A98;
	}

	if(a6 != level->getData(x, y, z)) {
		return &this->field_A80;
	}

	if(this->isLit) return &this->field_A68;
	return &this->field_A50;
}
int32_t FurnaceTile::getTileEntityType() {
	return 1;
}
void FurnaceTile::animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	float v8;  // s19
	int32_t v9;	   // r5
	float v10; // s17
	float v11; // s18
	float v12; // s15
	float v13; // s18
	float v14; // s19
	float v15; // s18
	float v16; // s19
	float v17; // s19
	float v18; // s18

	if(this->isLit) {
		v8 = (float)x + 0.5;
		v9 = level->getData(x, y, z);
		v10 = (float)((float)y + 0.0) + (float)((float)(rng->nextFloat() * 6.0) * 0.0625);
		v11 = (float)z + 0.5;
		v12 = (float)(rng->nextFloat() * 0.6) - 0.3;
		switch(v9) {
			case 4:
				v13 = v11 + v12;
				v14 = v8 - 0.52;
LABEL_8:
				level->addParticle(PT_SMOKE, v14, v10, v13, 0.0, 0.0, 0.0, 0);
				level->addParticle(PT_FLAME, v14, v10, v13, 0.0, 0.0, 0.0, 0);
				return;
			case 5:
				v15 = v11 + v12;
				v16 = v8 + 0.52;
				level->addParticle(PT_SMOKE, v16, v10, v15, 0.0, 0.0, 0.0, 0);
				level->addParticle(PT_FLAME, v16, v10, v15, 0.0, 0.0, 0.0, 0);
				return;
			case 2:
				v14 = v8 + v12;
				v13 = v11 - 0.52;
				goto LABEL_8;
			case 3:
				v17 = v8 + v12;
				v18 = v11 + 0.52;
				level->addParticle(PT_SMOKE, v17, v10, v18, 0.0, 0.0, 0.0, 0);
				level->addParticle(PT_FLAME, v17, v10, v18, 0.0, 0.0, 0.0, 0);
				break;
		}
	}
}
void FurnaceTile::onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t n;			   // r7
	FurnaceTileEntity* te; // r6
	ItemInstance* v9;	   // r10
	float v10;			   // s20
	float v11;			   // s21
	float v12;			   // s22
	int32_t v13;		   // r1
	int32_t count;		   // r8
	Item* itemClass;	   // r1
	int32_t AuxValue;	   // r0
	ItemEntity* v17;	   // r8
	Item* v18;			   // [sp+Ch] [bp-6Ch]
	ItemInstance v21;	   // [sp+1Ch] [bp-5Ch] BYREF

	if(!FurnaceTile::noDrop) {
		n = 0;
		if(!level->isClientMaybe) {
			te = (FurnaceTileEntity*)level->getTileEntity(x, y, z);
			if(te) {
				while(n < te->getContainerSize()) {
					v9 = te->getItem(n);
					if(v9) {
						v10 = (float)(this->rand.nextFloat() * 0.8) + 0.1;
						v11 = (float)(this->rand.nextFloat() * 0.8) + 0.1;
						v12 = (float)(this->rand.nextFloat() * 0.8) + 0.1;
						while(v9->count > 0) {
							v13 = this->rand.genrand_int32() % 0x15 + 10;
							if(v13 >= v9->count) {
								count = v9->count;
							} else {
								count = v13;
							}
							itemClass = v9->itemClass;
							v9->count -= count;
							v18 = itemClass;
							AuxValue = v9->getAuxValue();
							v17 = new ItemEntity(level, (float)x + v10, (float)y + v11, (float)z + v12, ItemInstance(v18, count, AuxValue));
							v17->motionX = this->rand.nextGaussian() * 0.05;
							v17->motionY = (float)(this->rand.nextGaussian() * 0.05) + 0.2;
							v17->motionZ = this->rand.nextGaussian() * 0.05;
							level->addEntity(v17);
						}
					}
					++n;
				}
			}
		}
	}
	EntityTile::onRemove(level, x, y, z);
}
int32_t FurnaceTile::getResource(int32_t a2, Random* a3) {
	return Tile::furnace->blockID;
}
bool_t FurnaceTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	if(!level->isClientMaybe) {
		TileEntity* te = level->getTileEntity(x, y, z);
		if(te) {
			player->openFurnace((FurnaceTileEntity*)te);
		}
	}
	return 1;
}
int32_t FurnaceTile::getPlacementDataValue(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, float a7, float a8, float a9, Mob* a10, int32_t a11) {
	float v11;	 // s15
	int32_t v12; // r3
	int32_t v13; // r3

	v11 = (float)((float)(a10->yaw * 4.0) / 360.0) + 0.5;
	v12 = (int32_t)v11;
	if(v11 < (float)(int32_t)v11) {
		v12 = v12 - 1; //lobyte(v12) =
	}
	v13 = v12 & 3;
	switch(v13) {
		case 0:
			return a11 | 2;
		case 1:
			return a11 | 5;
		case 2:
			return a11 | 3;
	}
	return a11 | 4;
}
