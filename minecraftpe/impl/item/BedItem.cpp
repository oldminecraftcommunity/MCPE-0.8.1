#include <item/BedItem.hpp>
#include <tile/Tile.hpp>
#include <level/Level.hpp>
#include <entity/Player.hpp>

BedItem::BedItem(int32_t id)
	: Item(id) {
}
BedItem::~BedItem() {
}
bool_t BedItem::useOn(ItemInstance* a2, Player* a3, Level* a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, float a9, float a10, float a11) {
	int32_t v12;   // r6
	float v13;	   // s15
	int32_t v14;   // r5
	int32_t v15;   // r5
	int32_t v16;   // r10
	int32_t v17;   // r9
	int32_t v18;   // r9
	int32_t v19;   // r10
	int32_t v21;   // r0
	Tile* v22;	   // [sp+10h] [bp-30h]

	if(a8 != 1) {
		return 0;
	}
	v12 = a6 + 1;
	v22 = Tile::bed;
	v13 = (float)((float)(a3->yaw * 4.0) / 360.0) + 0.5;
	v14 = (int32_t)v13;
	if(v13 < (float)(int32_t)v13) {
		v14 = v14 - 1; /*lobyte(v14) = ...*/
	}
	v15 = v14 & 3;
	if(v15) {
		if(v15 == 1) {
			v17 = -1;
			v16 = 0;
		} else if(v15 == 2) {
			v17 = 0;
			v16 = -1;
		} else {
			v16 = 0;
			v17 = 1;
		}
	} else {
		v17 = 0;
		v16 = 1;
	}
	if(!a4->isEmptyTile(a5, a6 + 1, a7)) {
		return 0;
	}
	v18 = v17 + a5;
	v19 = v16 + a7;
	if(!a4->isEmptyTile(v18, a6 + 1, v19) || !a4->isSolidBlockingTile(a5, a6, a7) || !a4->isSolidBlockingTile(v18, a6, v19)) {
		return 0;
	}
	a4->setTileAndData(a5, v12, a7, v22->blockID, v15, 3);
	v21 = a4->getTile(a5, v12, a7);
	if(v21 == v22->blockID) {
		a4->setTileAndData(v18, v12, v19, v21, v15 + 8, 3);
	}
	--a2->count;
	return 1;
}
