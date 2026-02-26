#include <item/SeedItem.hpp>
#include <level/Level.hpp>

SeedItem::SeedItem(int32_t id, int32_t plantId, int32_t placeId)
	: Item(id) {
	this->placeId = placeId;
	this->plantId = plantId;
}

SeedItem::~SeedItem() {
}
bool_t SeedItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	if(face != 1 || level->getTile(x, y, z) != this->placeId || !level->isEmptyTile(x, y + 1, z)) {
		return 0;
	}
	level->setTile(x, y + 1, z, this->plantId, 3);
	--item->count;
	return 1;
}
bool_t SeedItem::isSeed() {
	return 1;
}
