#include <item/WeaponItem.hpp>
#include <tile/Tile.hpp>

WeaponItem::WeaponItem(int32_t a2, const Item::Tier& a3)
	: Item(a2) {
	this->tier = a3;
	this->maxStackSize = 1;
	this->setMaxDamage(a3.durability);
	this->damage = a3.damageAgainstEntity + 4;
}

WeaponItem::~WeaponItem() {
}
ItemInstance* WeaponItem::use(ItemInstance* a2, Level*, Player*) {
	return a2;
}
int32_t WeaponItem::getMaxUseDuration() {
	return 72000;
}
float WeaponItem::getDestroySpeed(ItemInstance* a2, Tile* a3) {
	if(a3->blockID == Tile::web->blockID) return 15.0;
	return 1.5f;
}
bool_t WeaponItem::canDestroySpecial(const Tile* a2) {
	return a2->blockID == Tile::web->blockID;
}
int32_t WeaponItem::getAttackDamage(Entity*) {
	return this->damage;
}
void WeaponItem::hurtEnemy(ItemInstance* a2, Mob* a3, Mob* a4) {
	a2->hurtAndBreak(1, a4);
}
bool_t WeaponItem::mineBlock(ItemInstance* a2, int32_t, int32_t, int32_t, int32_t, Mob* a7) {
	a2->hurtAndBreak(2, a7);
	return 1;
}
bool_t WeaponItem::isHandEquipped() {
	return 1;
}
