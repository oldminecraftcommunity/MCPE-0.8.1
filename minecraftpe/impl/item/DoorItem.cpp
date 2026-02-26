#include <item/DoorItem.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>

void DoorItem::place(Level* level, int32_t x, int32_t y, int32_t z, int32_t a5, struct Tile* a6) {
	int32_t v9; // r7
	int32_t v10; // r9
	int32_t v11; // r9
	int32_t v12; // r11
	int32_t v13; // r11
	bool_t v14; // r7
	bool_t v15; // r11
	int32_t v16; // r2
	int32_t v17; // [sp+14h] [bp-44h]
	int32_t v19; // [sp+20h] [bp-38h]
	int32_t v20; // [sp+24h] [bp-34h]
	int32_t v21; // [sp+28h] [bp-30h]
	int32_t v22; // [sp+2Ch] [bp-2Ch]

	if(a5) {
		if(a5 == 1) {
			v9 = 0;
			v10 = -1;
			goto LABEL_11;
		}
		if(a5 == 2) {
			v9 = -1;
		} else {
			v9 = 0;
			if(a5 == 3) {
				v10 = 1;
				goto LABEL_11;
			}
		}
	} else {
		v9 = 1;
	}
	v10 = 0;
LABEL_11:
	v20 = z - v9;
	v19 = x - v10;
	v11 = v10 + x;
	v12 = level->isSolidBlockingTile(v19, y, z - v9);
	v21 = v12 + level->isSolidBlockingTile(v19, y + 1, z - v9);
	v13 = z + v9;
	v17 = level->isSolidBlockingTile(v11, y, z + v9);
	v22 = v17 + level->isSolidBlockingTile(v11, y + 1, z + v9);
	v14 = level->getTile(v19, y, z - v9) == a6->blockID || level->getTile(v19, y + 1, v20) == a6->blockID;
	v15 = level->getTile(v11, y, v13) != a6->blockID && level->getTile(v11, y + 1, v13) != a6->blockID && v14 || v22 > v21;
	level->setTileAndData(x, y, z, a6->blockID, a5, 2);
	if(v15) {
		v16 = 9;
	} else {
		v16 = 8;
	}
	level->setTileAndData(x, y + 1, z, a6->blockID, v16, 2);
	level->updateNeighborsAt(x, y, z, a6->blockID);
	level->updateNeighborsAt(x, y + 1, z, a6->blockID);
}
DoorItem::DoorItem(int32_t id, Material* mat)
	: Item(id) {
	this->field_48 = mat;
	this->maxItemdamage = 64;
	this->maxStackSize = 1;
}

DoorItem::~DoorItem() {
}
bool_t DoorItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	Tile* v15;	 // r4
	float v17;	 // s15
	int32_t v18; // r5

	if(face != 1) {
		return 0;
	}
	if(this->field_48 == Material::wood) {
		v15 = Tile::door_wood;
	} else {
		v15 = Tile::door_iron;
	}

	if(v15->mayPlace(level, x, y + 1, z)) {
		v17 = (float)((float)((float)(player->yaw + 180.0) * 4.0) / 360.0) - 0.5;
		v18 = (int32_t)v17;
		if(v17 < (float)(int32_t)v17) {
			/*LOBYTE(v18)*/ v18 = v18 - 1;
		}
		DoorItem::place(level, x, y + 1, z, v18 & 3, v15);
		--item->count;
		return 1;
	}
	return 0;
}
