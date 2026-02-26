#include <item/TileItem.hpp>
#include <tile/Tile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

TileItem::TileItem(int32_t id)
	: Item(id) {
	this->blockID = id + 256;
	this->setIcon(*Tile::tiles[this->blockID]->getTexture(2));
}

TileItem::~TileItem() {
}
bool_t TileItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t side, float faceX, float faceY, float faceZ) {
	int32_t yNew;	  // r5
	int32_t zNew;	  // r6
	int32_t sideNew;  // r9
	int32_t blockID;  // r2
	Tile* v19;		  // r3
	Tile* v20;		  // r11
	int32_t auxValue; // r0
	int32_t meta;	  // r0
	int32_t v23;	  // r0

	yNew = y;
	zNew = z;
	sideNew = side;
	if(level->adventureSettings.allowInteract) {
		blockID = this->blockID;
		if(blockID != Tile::leaves->blockID && Tile::tiles[blockID]->material != Material::plant) {
			return 0;
		}
	}
	v19 = Tile::tiles[level->getTile(x, y, z)];
	if(v19 && v19->replaceable) {
		sideNew = 1;
	} else {
		switch(side) {
			case 0:
				yNew = y - 1;
				break;
			case 1:
				yNew = y + 1;
				break;
			case 2:
				zNew = z - 1;
				break;
			case 3:
				zNew = z + 1;
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
	if(!item->count || !level->mayPlace(this->blockID, x, yNew, zNew, 0, sideNew)) {
		return 0;
	}
	v20 = Tile::tiles[this->blockID];
	auxValue = item->getAuxValue();
	meta = this->getLevelDataForAuxValue(auxValue);
	v23 = v20->getPlacementDataValue(level, x, yNew, zNew, sideNew, faceX, faceY, faceZ, (Mob*)player, meta);
	if(level->setTileAndData(x, yNew, zNew, this->blockID, v23, 3)) {
		level->playSound((float)x + 0.5, (float)yNew + 0.5, (float)zNew + 0.5, v20->soundType->field_C, (float)(v20->soundType->field_0 + 1.0) * 0.5, v20->soundType->field_4 * 0.8);
		--item->count;
	}
	return 1;
}
std::string TileItem::getDescriptionId() {
	return Tile::tiles[this->blockID]->getDescriptionId();
}
std::string TileItem::getDescriptionId(const ItemInstance* a3){
	return Tile::tiles[this->blockID]->getDescriptionId(a3);
}
bool_t TileItem::isEmissive(int32_t a2) {
	int32_t blockID; // r2

	blockID = this->blockID;
	return blockID == Tile::torch->blockID || blockID == Tile::glowingObsidian->blockID || blockID == Tile::lightGem->blockID;
}
