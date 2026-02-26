#include <item/MinecartItem.hpp>
#include <level/Level.hpp>
#include <tile/BaseRailTile.hpp>
#include <entity/Minecart.hpp>

MinecartItem::MinecartItem(int32_t a2, int32_t a3)
	: Item(a2) {
	this->type = a3;
	this->setMaxStackSize(1);
}

MinecartItem::~MinecartItem() {
}
bool_t MinecartItem::useOn(ItemInstance* item, Player* player, struct Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	int32_t v14;   // r0
	bool_t result; // r0

	v14 = level->getTile(x, y, z);
	result = BaseRailTile::isRail(v14);
	if(result) {
		if(!level->isClientMaybe) {
			level->addEntity(Minecart::createMinecart(level, (float)x + 0.5, (float)y + 0.5, (float)z + 0.5, this->type));
		}
		result = 1;
		--item->count;
	}
	return result;
}
