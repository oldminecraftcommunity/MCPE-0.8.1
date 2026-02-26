#include <item/HoeItem.hpp>
#include <tile/Tile.hpp>
#include <level/Level.hpp>
#include <entity/ItemEntity.hpp>
#include <entity/Player.hpp>

HoeItem::HoeItem(int32_t id, Item::Tier t)
	: Item(id) {
	this->tier = t;
	this->maxStackSize = 1;
	this->setMaxDamage(t.durability);
}

HoeItem::~HoeItem() {
}
bool_t HoeItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fX, float fY, float fZ) {
	int32_t v14;	 // r8
	int32_t result;	 // r0
	Tile* v16;		 // r6
	Item* v17;		 // r6
	ItemEntity* v18; // r5
	float v19;		 // s14
	float v20;		 // s23
	float v21;		 // s14
	uint32_t v23;	 // r0
	float v24;		 // s16

	v14 = level->getTile(x, y, z);
	result = level->getTile(x, y + 1, z);
	if(!face || result) {
		return 0;
	}
	if(v14 == Tile::grass->blockID || v14 == Tile::dirt->blockID) {
		v16 = Tile::farmland;
		level->playSound((float)x + 0.5, (float)y + 0.5, (float)z + 0.5, Tile::farmland->soundType->field_C, (float)(Tile::farmland->soundType->field_0 + 1.0) * 0.5, Tile::farmland->soundType->field_4 * 0.8);
		item->hurtAndBreak(1, player);
		if(!level->isClientMaybe) {
			level->setTile(x, y, z, v16->blockID, 3);
			if(v14 == Tile::grass->blockID && !(level->random.genrand_int32() << 29)) {
				v19 = level->random.nextFloat();
				v20 = (float)(v19 * 0.7) + 0.15;
				v21 = level->random.nextFloat();
				v24 = level->random.nextFloat();
				v23 = level->random.genrand_int32();
				v17 = Item::seeds_wheat;
				if(!(v23 % 0xF)) {
					v17 = Item::seeds_beetroot;
				}
				v18 = new ItemEntity(level, (float)x + v20, (float)y + (float)((float)(v21 * 0.7) + 0.75), (float)z + (float)((float)(v24 * 0.7) + 0.15), {v17});
				v18->delayBeforePickup = 10;
				level->addEntity(v18);
			}
		}
		return 1;
	}
	return 0;
}
bool_t HoeItem::isHandEquipped() {
	return 1;
}
