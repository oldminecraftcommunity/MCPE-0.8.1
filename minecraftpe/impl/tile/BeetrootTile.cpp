#include <tile/BeetrootTile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <entity/ItemEntity.hpp>

BeetrootTile::BeetrootTile(int32_t a2)
	: CropTile(a2, "wheat_stage_x") {
	this->texture3 = *this->getTextureItem("beetroot_stage_x");
}
void BeetrootTile::spawnItem(Level* level, int32_t x, int32_t y, int32_t z, const struct ItemInstance& item) {
	float v11; // s8
	ItemEntity* v12; // r5
	float v13; // s10
	float v14; // s14

	v11 = level->random.nextFloat();
	v13 = level->random.nextFloat();
	v14 = level->random.nextFloat();
	v12 = new ItemEntity(level, (float)x + (float)((float)(v11 * 0.7) + 0.15), (float)y + (float)((float)(v13 * 0.7) + 0.15), (float)z + (float)((float)(v14 * 0.7) + 0.15), item);
	v12->delayBeforePickup = 10;
	level->addEntity(v12);
}

BeetrootTile::~BeetrootTile() {
}
TextureUVCoordinateSet* BeetrootTile::getTexture(int32_t a2, int32_t a3) {
	int32_t v4; // r1

	if(a3 > 6) {
		v4 = 3;
	} else {
		if(a3 == 6) {
			a3 = 5;
		}
		v4 = a3 >> 1;
	}
	return this->texture3.getUV(v4);
}
void BeetrootTile::spawnResources(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, float a7) {
	const Item* v11;	  // r0
	int32_t v13;		  // r11
	int8_t v14;			  // r0
	int32_t v15;		  // r12
	int32_t v16;		  // r10
	const Item* v17;	  // r0
	int32_t i;			  // r11
	bool_t isClientMaybe; // [sp+Ch] [bp-44h]
	int32_t v20;		  // [sp+Ch] [bp-44h]

	if(!level->isClientMaybe && a6 > 1) {
		if(a6 > 6) {
			isClientMaybe = level->isClientMaybe;
			v13 = level->random.genrand_int32() % 3;
			v14 = level->random.genrand_int32();
			v15 = isClientMaybe;
			v16 = v14 & 1;
			while(v15 < v13) {
				v20 = v15;
				v17 = this->getBaseSeed();

				this->spawnItem(level, x, y, z, ItemInstance(v17));
				v15 = v20 + 1;
			}
			for(i = 0; i <= v16; ++i) {
				this->spawnItem(level, x, y, z, ItemInstance(Item::beetroot));
			}
		} else {
			v11 = this->getBaseSeed();
			this->spawnItem(level, x, y, z, ItemInstance(v11));
		}
	}
}
struct Item* BeetrootTile::getBaseSeed() {
	return Item::seeds_beetroot;
}

int32_t BeetrootTile::getBasePlantId() {
	return Item::beetroot->itemID;
}
