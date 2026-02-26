#include <item/DiggerItem.hpp>
#include <tile/Tile.hpp>

void DiggerItem::setTiles(const std::vector<Tile*>& a2) {
	for(int i = 0; i != 256; ++i) {
		this->field_5C[i] = 0;
	}

	for(Tile* t: a2) {
		this->field_5C[t->blockID] = 1;
	}
	this->field_50 = a2;
}


DiggerItem::DiggerItem(int32_t a2, const Item::Tier& a3)
	: Item(a2)
	, tier(&a3) {
	std::vector<Tile*> tiles;
	this->efficiencyMultiplier = a3.efficienctMultiplier;
	this->setTiles(tiles);
	this->maxStackSize = 1;
	this->setMaxDamage(a3.durability);
	this->damageAgainstEntity = a3.damageAgainstEntity + 2;
}
DiggerItem::~DiggerItem() {
}
float DiggerItem::getDestroySpeed(ItemInstance* a2, Tile* a3) {
	if(a3 && this->field_5C[a3->blockID]) {
		printf("%f\n", this->efficiencyMultiplier);
		return this->efficiencyMultiplier;
	} else {
		return 1.0;
	}
}
int32_t DiggerItem::getAttackDamage(Entity*) {
	return this->damageAgainstEntity;
}
void DiggerItem::hurtEnemy(ItemInstance* a2, Mob* a3, Mob* a4) {
	a2->hurtAndBreak(2, a4);
}
bool_t DiggerItem::mineBlock(ItemInstance* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, Mob* a7) {
	a2->hurtAndBreak(1, a7);
	return 1;
}
bool_t DiggerItem::isHandEquipped() {
	return 1;
}
