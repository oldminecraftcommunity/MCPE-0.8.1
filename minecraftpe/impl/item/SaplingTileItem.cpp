#include <item/SaplingTileItem.hpp>
#include <tile/Tile.hpp>

SaplingTileItem::SaplingTileItem(int32_t id)
	: TileItem(id) {
	this->setMaxDamage(0);
	this->setStackedByData(1);
}
SaplingTileItem::~SaplingTileItem() {
}
TextureUVCoordinateSet* SaplingTileItem::getIcon(int32_t a2, int32_t, bool_t) {
	return Tile::sapling->getTexture(0, a2);
}
int32_t SaplingTileItem::getLevelDataForAuxValue(int32_t a2) {
	return a2;
}
