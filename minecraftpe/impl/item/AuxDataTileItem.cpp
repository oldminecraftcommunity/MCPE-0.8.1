#include <item/AuxDataTileItem.hpp>
#include <tile/Tile.hpp>
#include <I18n.hpp>

AuxDataTileItem::AuxDataTileItem(int32_t id, Tile* t)
	: TileItem(id) {
	this->tile = t;
	this->setMaxDamage(0);
	this->setStackedByData(1);
}

AuxDataTileItem::~AuxDataTileItem() {
}
TextureUVCoordinateSet* AuxDataTileItem::getIcon(int32_t a2, int32_t a3, bool_t a4) {
	return this->tile->getCarriedTexture(2, a2);
}
int32_t AuxDataTileItem::getLevelDataForAuxValue(int32_t a2) {
	return a2;
}
std::string AuxDataTileItem::getName(const ItemInstance* a2) {
	std::string v9 = this->tile->getTypeDescriptionId(a2->getAuxValue());
	if(v9.length()) {
		return I18n::get(this->getDescriptionId() + "." + v9 + ".name");
	} else {
		return Item::getName(a2);
	}
}
std::string AuxDataTileItem::getDescription(const ItemInstance* a2) {
	std::string v10 = this->tile->getTypeDescriptionId(a2->getAuxValue());
	if(v10.length()) {
		return this->getDescriptionId() + "." + v10;
	} else {
		return Item::getDescription(a2);
	}
}

