#include <tile/CropTile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <entity/ItemEntity.hpp>
#include <tile/material/Material.hpp>

CropTile::CropTile(int32_t id, const std::string& a3)
	: Bush(id, a3, Material::plant) {
	this->setTicking(1);
	this->setShape(0, 0, 0, 1, 0.25, 1);
	this->texture2 = *this->getTextureItem("wheat_stage_x");
}
float CropTile::getGrowthSpeed(Level* level, int32_t x, int32_t y, int32_t z){
	int32_t xneg;		  // r5
	int32_t idxposzneg;	  // r8
	int32_t idxposzpos;	  // r6
	int32_t idxnegzpos;	  // r0
	int32_t blockID;	  // r3
	bool_t anyOnX;	  // r2
	bool_t anyOnZ;	  // r2
	bool_t anyOnDiag; // r8
	float v16;		  // s16
	int32_t v17;		  // r11
	float v18;		  // s15
	int32_t zz;			  // r6
	int32_t idxneg;		  // [sp+4h] [bp-54h]
	bool_t anyOnX_;	  // [sp+4h] [bp-54h]
	int32_t zneg;		  // [sp+8h] [bp-50h]
	bool_t anyOnZ_;	  // [sp+8h] [bp-50h]
	int32_t idzpos;		  // [sp+10h] [bp-48h]
	int32_t idxpos;		  // [sp+14h] [bp-44h]
	int32_t idxnegzneg;	  // [sp+18h] [bp-40h]

	zneg = level->getTile(x, y, z - 1);
	xneg = x - 1;
	idzpos = level->getTile(x, y, z + 1);
	idxneg = level->getTile(x - 1, y, z);
	idxpos = level->getTile(x + 1, y, z);
	idxnegzneg = level->getTile(x - 1, y, z - 1);
	idxposzneg = level->getTile(x + 1, y, z - 1);
	idxposzpos = level->getTile(x + 1, y, z + 1);
	idxnegzpos = level->getTile(x - 1, y, z + 1);
	blockID = this->blockID;
	anyOnX = idxneg == blockID || idxpos == blockID;
	anyOnX_ = anyOnX;
	anyOnZ = zneg == blockID || idzpos == blockID;
	anyOnZ_ = anyOnZ;
	anyOnDiag = idxnegzneg == blockID || idxposzneg == blockID || idxposzpos == blockID || idxnegzpos == blockID;
	v16 = 1.0;
	v17 = y - 1;
	while(xneg <= x + 1) {
		for(zz = z - 1; zz <= z + 1; ++zz) {
			if(level->getTile(xneg, v17, zz) == Tile::farmland->blockID) {
				if(level->getData(xneg, v17, zz) > 0) {
					v18 = 3.0;
				} else {
					v18 = 1.0;
				}
			} else {
				v18 = 0.0;
			}
			if(xneg != x || zz != z) {
				v18 = v18 * 0.25;
			}
			v16 = v16 + v18;
		}
		++xneg;
	}
	if(anyOnDiag || anyOnX_ && anyOnZ_) {
		return v16 * 0.5;
	}
	return v16;
}

CropTile::~CropTile() {
}
bool_t CropTile::onFertilized(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t data = level->getData(x, y, z);
	int32_t v9 = level->random.genrand_int32() % 3 + data + 2;
	if(v9 >= 7) v9 = 7;
	level->setData(x, y, z, v9, 2);
	return 1;
}
int32_t CropTile::getRenderShape() {
	return 6;
}
TextureUVCoordinateSet* CropTile::getTexture(int32_t a2, int32_t a3) {
	if(a3 < 0) a3 = 0;
	return this->texture2.getUV(a3);
}
TextureUVCoordinateSet* CropTile::getTexture(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	int32_t v7 = level->getData(x, y, z);
	if(v7 < 0) v7 = 7;
	return this->texture2.getUV(v7);
}
void CropTile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
	this->checkAlive(level, x, y, z);
	if(level->getRawBrightness(x, y, z) > 8) {
		int32_t meta = level->getData(x, y, z);
		if(meta <= 6) {
			float speed = this->getGrowthSpeed(level, x, y, z);
			if(rng->genrand_int32() % (int32_t)(25.0 / speed)) {
				level->setData(x, y, z, meta + 1, 2);
			}
		}
	}
}
int32_t CropTile::getResource(int32_t a2, Random*) {
	if(a2 == 7) return this->getBasePlantId();
	return -1;
}
int32_t CropTile::getResourceCount(Random*) {
	return 1;
}
void CropTile::spawnResources(Level* level, int32_t a3, int32_t a4, int32_t a5, int32_t a6, float a7) {
	int32_t v11;	 // r6
	const Item* v15; // r0
	float v16;		 // s10
	ItemEntity* v17; // r5
	float v18;		 // s12
	float v19;		 // s14

	Tile::spawnResources(level, a3, a4, a5, a6, a7);
	if(!level->isClientMaybe) {
		v11 = 3;
		do {
			if((int32_t)(level->random.genrand_int32() % 0xF) <= a6) {
				v15 = (const Item*)this->getBaseSeed();
				v16 = level->random.nextFloat();
				v18 = level->random.nextFloat();
				v19 = level->random.nextFloat();
				v17 = new ItemEntity(level, (float)a3 + (float)((float)(v16 * 0.7) + 0.15), (float)a4 + (float)((float)(v18 * 0.7) + 0.15), (float)a5 + (float)((float)(v19 * 0.7) + 0.15), ItemInstance(v15));
				v17->delayBeforePickup = 10;
				level->addEntity(v17);
			}
			--v11;
		} while(v11);
	}
}
bool_t CropTile::mayPlaceOn(int32_t a2) {
	return a2 == Tile::farmland->blockID;
}
struct Item* CropTile::getBaseSeed() {
	return Item::seeds_wheat;
}

int32_t CropTile::getBasePlantId() {
	return Item::wheat->itemID;
}
