#include <item/LeafTileItem.hpp>
#include <tile/Tile.hpp>
LeafTileItem::LeafTileItem(int32_t id)
	: TileItem(id) {
	this->setMaxDamage(0);
	this->setStackedByData(1);
}
LeafTileItem::~LeafTileItem() {
}
TextureUVCoordinateSet* LeafTileItem::getIcon(int32_t a2, int32_t, bool_t) {
	return Tile::leaves->getTexture(0, a2);
}
int32_t LeafTileItem::getLevelDataForAuxValue(int32_t a2) {
	return a2 | 8;
}
