#include <item/FlintAndSteelItem.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>

FlintAndSteelItem::FlintAndSteelItem(int32_t id)
	: Item(id) {
	this->setMaxStackSize(1);
	this->setMaxDamage(64);
}

FlintAndSteelItem::~FlintAndSteelItem() {
}
bool_t FlintAndSteelItem::useOn(ItemInstance* a2, Player* a3, Level* a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, float a9, float a10, float a11) {
	int32_t v14; // r6
	int32_t v15; // r5
	int32_t v16; // r4
	float f; // r0

	v14 = a5;
	v15 = a6;
	v16 = a7;
	if(a8) {
		switch(a8) {
			case 1:
				v15 = a6 + 1;
				break;
			case 2:
				v16 = a7 - 1;
				break;
			case 3:
				v16 = a7 + 1;
				break;
			case 4:
				v14 = a5 - 1;
				break;
			case 5:
				v14 = a5 + 1;
				break;
		}
	} else {
		v15 = a6 - 1;
	}
	if(!a4->getTile(v14, v15, v16)) {
		f = a4->random.nextFloat();
		a4->playSound((float)v14 + 0.5, (float)v15 + 0.5, (float)v16 + 0.5, "fire.ignite", 1.0, (float)(f * 0.4) + 0.8);
		a4->setTile(v14, v15, v16, Tile::fire->blockID, 3);
	}
	if(!a3->abilities.instabuild) {
		a2->hurtAndBreak(1, (Mob*)a3);
	}
	return 1;
}
