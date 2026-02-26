#include <item/TilePlanterItem.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>

TilePlanterItem::TilePlanterItem(int32_t id, Tile* tile)
	: Item(id) {
	this->blockID = tile->blockID;
}

TilePlanterItem::~TilePlanterItem() {
}
bool_t TilePlanterItem::useOn(ItemInstance* item, Player* player, struct Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	int32_t v13;	  // r5
	int32_t v14;	  // r6
	int32_t v15;	  // r8
	Tile* v18;		  // r2
	Tile* v20;		  // r11
	int32_t AuxValue; // r0
	int32_t v22;	  // r0

	v13 = y;
	v14 = z;
	v15 = face;
	v18 = Tile::tiles[level->getTile(x, y, z)];
	if(v18 && v18->replaceable) {
		v15 = 1;
	} else {
		switch(face) {
			case 0:
				v13 = y - 1;
				break;
			case 1:
				v13 = y + 1;
				break;
			case 2:
				v14 = z - 1;
				break;
			case 3:
				v14 = z + 1;
				break;
			case 4:
				--x;
				break;
			case 5:
				++x;
				break;
			default:
				break;
		}
	}

	if(item->count) {
		if(level->mayPlace(this->blockID, x, v13, v14, 0, v15)) {
			v20 = Tile::tiles[this->blockID];
			if(v20) {
				v22 = v20->getPlacementDataValue(level, x, v13, v14, v15, fx, fy, fz, (Mob*)player, item->getAuxValue());
				if(level->setTileAndData(x, v13, v14, this->blockID, v22, 3)) {
					level->playSound((float)x + 0.5, (float)v13 + 0.5, (float)v14 + 0.5, v20->soundType->field_C, (float)(v20->soundType->field_0 + 1.0) * 0.5, v20->soundType->field_4 * 0.8);
					--item->count;
				}
			}
		}
		return 1;
	}
	return 0;
}
bool_t TilePlanterItem::isEmissive(int32_t) {
	return this->blockID == Tile::torch->blockID || this->blockID == Tile::glowingObsidian->blockID || this->blockID == Tile::lightGem->blockID;
}
