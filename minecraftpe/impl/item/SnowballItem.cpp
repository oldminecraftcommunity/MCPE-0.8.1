#include <item/SnowballItem.hpp>
#include <entity/Snowball.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>

SnowballItem::SnowballItem(int id)
	: Item(id) {
	this->maxStackSize = 16;
}
SnowballItem::~SnowballItem() {
}
ItemInstance* SnowballItem::use(ItemInstance* a2, Level* a3, Player* a4) {
	if(!a4->abilities.instabuild) {
		--a2->count;
	}
	a3->playSound(a4, "random.bow", 0.5, 0.4 / (float)((float)(Item::random.nextFloat() * 0.4) + 0.8));
	if(!a3->isClientMaybe) {
		a3->addEntity(new Snowball(a3, a4));
	}
	return a2;
}
