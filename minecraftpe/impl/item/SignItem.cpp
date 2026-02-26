#include <item/SignItem.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <tile/Tile.hpp>
#include <entity/Player.hpp>

SignItem::SignItem(int32_t id)
	: Item(id) {
	this->maxStackSize = 16;
}

SignItem::~SignItem() {
}
bool_t SignItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz){
	int32_t v14;	// r5
	int32_t v15;	// r7
	int32_t v16;	// r4
	int32_t result; // r0
	Material* v18;	// r0
	float v19;		// s15
	int32_t v20;	// r3
	TileEntity* te; // r1

	v14 = x;
	v15 = y;
	v16 = z;
	if(!face) {
		return 0;
	}
	v18 = level->getMaterial(x, y, z);
	if(!v18->isSolid()) {
		return 0;
	}
	switch(face) {
		case 1:
			v15 = y + 1;
			break;
		case 2:
			v16 = z - 1;
			break;
		case 3:
			v16 = z + 1;
			break;
		case 4:
			v14 = x - 1;
			break;
		case 5:
			v14 = x + 1;
			break;
	}
	result = Tile::sign->mayPlace(level, v14, v15, v16);
	if(result) {
		if(face == 1) {
			v19 = (float)((float)((float)(player->yaw + 180.0) * 16.0) / 360.0) + 0.5;
			v20 = (int32_t)v19;
			if(v19 < (float)(int32_t)v19) {
				/*LOBYTE(v20)*/ v20 = v20 - 1;
			}
			level->setTileAndData(v14, v15, v16, Tile::sign->blockID, v20 & 0xF, 3);
		} else {
			level->setTileAndData(v14, v15, v16, Tile::wallSign->blockID, face, 3);
		}
		--item->count;
		te = level->getTileEntity(v14, v15, v16);
		if(te) {
			player->openTextEdit(te);
		}
		return 1;
	}
	return result;
}
