#include <item/ArmorItem.hpp>

int32_t ArmorItem::healthPerSlot[] = {0xB, 0x10, 0xF, 0xD};
ArmorItem::ArmorMaterial ArmorItem::CLOTH(5, 1, 3, 2, 1);
ArmorItem::ArmorMaterial ArmorItem::CHAIN(15, 2, 5, 4, 1);
ArmorItem::ArmorMaterial ArmorItem::IRON(15, 2, 6, 5, 2);
ArmorItem::ArmorMaterial ArmorItem::GOLD(7, 2, 5, 3, 1);
ArmorItem::ArmorMaterial ArmorItem::DIAMOND(33, 3, 8, 6, 3);

ArmorItem::ArmorMaterial::ArmorMaterial(int32_t h, int32_t d0, int32_t d1, int32_t d2, int32_t d3) {
	this->health = h;
	this->defenceForSlot[0] = d0;
	this->defenceForSlot[1] = d1;
	this->defenceForSlot[2] = d2;
	this->defenceForSlot[3] = d3;
}

int32_t ArmorItem::ArmorMaterial::getDefenseForSlot(int32_t a2) const {
	return this->defenceForSlot[a2];
}
int32_t ArmorItem::ArmorMaterial::getHealthForSlot(int32_t a2) const {
	return this->health + ArmorItem::healthPerSlot[a2];
}

ArmorItem::ArmorItem(int32_t id, const ArmorItem::ArmorMaterial& m, int32_t a4, int32_t a5)
	: Item(id) {
	this->field_48 = a5;
	this->field_50 = a4;
	this->armorMaterial = &m;
	this->defenseForSlot = m.getDefenseForSlot(a5);
	this->setMaxDamage(m.getHealthForSlot(a5));
	this->maxStackSize = 1;
}

ArmorItem::~ArmorItem() {
}
bool_t ArmorItem::isArmor() {
	return 1;
}
