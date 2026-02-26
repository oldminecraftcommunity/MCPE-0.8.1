#include <item/BowlFoodItem.hpp>

BowlFoodItem::BowlFoodItem(int32_t a2, int32_t a3)
	: FoodItem(a2, a3, 0.6, 0) {
	this->setMaxStackSize(1);
}
BowlFoodItem::~BowlFoodItem() {
}
ItemInstance BowlFoodItem::useTimeDepleted(ItemInstance* a3, Level* a4, Player* player) {
	ItemInstance v13 = FoodItem::useTimeDepleted(a3, a4, player);
	ItemInstance v14(Item::bowl);
	*a3 = v14; //TODO some weird loop
	return ItemInstance(*a3);
}
