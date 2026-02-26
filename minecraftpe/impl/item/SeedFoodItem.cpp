#include <item/SeedFoodItem.hpp>
#include <level/Level.hpp>

SeedFoodItem::SeedFoodItem(int32_t id, int32_t healAmount, float f48, int8_t f4C, int32_t plantID, int32_t placeID)
	: FoodItem(id, healAmount, f48, f4C) {
	this->plantId = plantID;
	this->placeId = placeID;
}
SeedFoodItem::~SeedFoodItem() {
}
bool_t SeedFoodItem::useOn(ItemInstance* item, Player* player, struct Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	if(face != 1 || level->getTile(x, y, z) != this->placeId || !level->isEmptyTile(x, y + 1, z)) {
		return 0;
	}
	level->setTile(x, y + 1, z, this->plantId, 3);
	--item->count;
	return 1;
}
