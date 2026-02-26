#include <item/FoodItem.hpp>
#include <level/Level.hpp>
#include <entity/Player.hpp>

FoodItem::FoodItem(int32_t id, int32_t healAmount, float f48, int8_t f4C)
	: Item(id) {
	this->field_48 = f48;
	this->field_4C = f4C;
	this->healAmount = healAmount;
}
FoodItem::~FoodItem() {
}
ItemInstance* FoodItem::use(ItemInstance* a2, struct Level* a3, Player* a4) {
	if(!a4->abilities.invulnerable && a4->isHurt()) {
		a4->startUsingItem(ItemInstance(*a2), this->getMaxUseDuration());
	}
	return a2;
}
int32_t FoodItem::getMaxUseDuration() {
	return 32;
}
ItemInstance FoodItem::useTimeDepleted(ItemInstance* a2, Level* level, Player* player) {
	--a2->count;
	player->heal(this->healAmount);
	level->playSound(player, "random.burp", 0.5, level->random.nextFloat()*0.1 + 0.9);
	return ItemInstance(*a2);
}
int32_t FoodItem::getUseAnimation() {
	return 1;
}
bool_t FoodItem::isFood() {
	return 1;
}
