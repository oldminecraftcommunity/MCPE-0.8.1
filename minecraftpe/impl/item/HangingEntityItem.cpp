#include <item/HangingEntityItem.hpp>
#include <entity/Painting.hpp>
#include <math/Direction.hpp>
#include <level/Level.hpp>

HangingEntityItem::HangingEntityItem(int32_t a2, int32_t a3)
	: Item(a2) {
	this->entityId = a3;
}
HangingEntity* HangingEntityItem::createEntity(Level* level, int32_t x, int32_t y, int32_t z, int32_t m) {
	if(this->entityId != 83) return 0;
	return new Painting(level, x, y, z, m);
}


HangingEntityItem::~HangingEntityItem() {
}
bool_t HangingEntityItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	HangingEntity* e; // r0
	Entity* v14;	  // r4

	if(!face || face == 1) {
		return 0;
	}
	e = this->createEntity(level, x, y, z, Direction::FACING_DIRECTION[face]);
	v14 = (Entity*)e;
	if(e) {
		if(e->survives()) {
			if(level->isClientMaybe) {
				delete v14;
			} else {
				level->addEntity(v14);
			}
			--item->count;
		} else {
			delete v14;
		}
	}
	return 1;
}
