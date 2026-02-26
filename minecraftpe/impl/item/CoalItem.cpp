#include <item/CoalItem.hpp>

CoalItem::CoalItem(int32_t id)
	: Item(id) {
	this->setStackedByData(1);
	this->setMaxDamage(0);
	this->field_48 = Item::getTextureUVCoordinateSet("charcoal", 0);

}
CoalItem::~CoalItem() {
}
TextureUVCoordinateSet* CoalItem::getIcon(int32_t a2, int32_t, bool_t) {
	if(a2 == 1) return &this->field_48;
	return &this->iconUV;
}
std::string CoalItem::getDescriptionId(const ItemInstance* a3) {
	if(a3->getAuxValue() == 1) {
		return Item::ICON_DESCRIPTION_PREFIX + "charcoal";
	}
	return Item::ICON_DESCRIPTION_PREFIX + "coal";
}
