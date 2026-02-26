#include <item/StoneSlabTileItem.hpp>
#include <tile/StoneSlabTile.hpp>
#include <I18n.hpp>
#include <level/Level.hpp>
StoneSlabTileItem::StoneSlabTileItem(int32_t id) : TileItem(id){
	this->setMaxDamage(0);
	this->setStackedByData(1);
}
StoneSlabTileItem::~StoneSlabTileItem() {
}
TextureUVCoordinateSet* StoneSlabTileItem::getIcon(int32_t a2, int32_t, bool_t) {
	return Tile::stoneSlabHalf->getTexture(2, a2);
}
bool_t StoneSlabTileItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float faceX, float faceY, float faceZ) {
	int32_t id;	  // r11
	uint32_t v15; // r0
	int32_t v16;  // r3
	int32_t v17;  // r11

	if(item->count) {
		id = level->getTile(x, y, z);
		v15 = level->getData(x, y, z);
		v16 = (v15 >> 3) & 1;
		if(face == 1) {
			if(v16) {
				return TileItem::useOn(item, player, level, x, y, z, face, faceX, faceY, faceZ);
			}
		} else if(face || !v16) {
			return TileItem::useOn(item, player, level, x, y, z, face, faceX, faceY, faceZ);
		}
		if(id == Tile::stoneSlabHalf->blockID) {
			v17 = v15 & 7;
			if(v17 == item->getAuxValue()) {
				if(level->isUnobstructed(*Tile::stoneSlab->getAABB(level, x, y, z))) {
					if(level->setTileAndData(x, y, z, Tile::stoneSlab->blockID, v17, 3)) {
						level->playSound((float)x + 0.5, (float)y + 0.5, (float)z + 0.5, Tile::stoneSlab->soundType->field_C, (float)(Tile::stoneSlab->soundType->field_0 + 1.0) * 0.5, Tile::stoneSlab->soundType->field_4 * 0.8);
						--item->count;
					}
				}
				return 1;
			}
		}
		return TileItem::useOn(item, player, level, x, y, z, face, faceX, faceY, faceZ);
	}
	return 0;
}
int32_t StoneSlabTileItem::getLevelDataForAuxValue(int32_t a2) {
	return a2;
}
std::string StoneSlabTileItem::getName(const ItemInstance* a3){
	int32_t meta = a3->getAuxValue();
	int32_t v6 = meta;
	if(meta < 0) {
		v6 = 0;
	} else if(meta >= 7) {
		v6 = 0;
	}
	return I18n::get(TileItem::getDescriptionId() + "." + StoneSlabTile::SLAB_NAMES[v6] + ".name");
}
std::string StoneSlabTileItem::getDescriptionId(const ItemInstance* a3) {
	int32_t meta = a3->getAuxValue();
	int32_t v6 = meta;
	if(meta < 0) {
		v6 = 0;
	} else if(meta >= 7) {
		v6 = 0;
	}
	return TileItem::getDescriptionId() + "." + StoneSlabTile::SLAB_NAMES[v6];
}
