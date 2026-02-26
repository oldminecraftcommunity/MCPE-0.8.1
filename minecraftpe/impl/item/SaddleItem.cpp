#include <item/SaddleItem.hpp>
#include <entity/Mob.hpp>

SaddleItem::SaddleItem(int32_t id) : Item(id){
	this->maxStackSize = 1;
}
SaddleItem::~SaddleItem() {
}
void SaddleItem::hurtEnemy(ItemInstance* a2, Mob* a3, Mob* a4) {
	if(a4->isPlayer()) {
		this->interactEnemy(a2, a3, (Player*)a4);
	}
}
void SaddleItem::interactEnemy(ItemInstance*, Mob*, Player*) {
}
