#include <item/ClothTileItem.hpp>
#include <tile/Tile.hpp>
#include <item/DyePowderItem.hpp>
#include <I18n.hpp>

ClothTileItem::ClothTileItem(int32_t id)
	: TileItem(id) {
	this->setMaxDamage(0);
	this->setStackedByData(1);
}
ClothTileItem::~ClothTileItem() {
}
TextureUVCoordinateSet* ClothTileItem::getIcon(int32_t a2, int32_t, bool_t) {
	return Tile::cloth->getTexture(2, a2);
}
int32_t ClothTileItem::getLevelDataForAuxValue(int32_t a2) {
	return a2;
}
std::string ClothTileItem::getName(const ItemInstance* a3) {
	return I18n::get(this->getDescriptionId() + "." + DyePowderItem::COLOR_DESCS[(~a3->getAuxValue()) & 0xF] + ".name");
}
std::string ClothTileItem::getDescription(const ItemInstance* a3) {
	return this->getDescriptionId() + "." + DyePowderItem::COLOR_DESCS[(~a3->getAuxValue()) & 0xF];
}
