#include <item/EggItem.hpp>
#include <entity/Player.hpp>
#include <entity/ThrownEgg.hpp>
#include <level/Level.hpp>

EggItem::EggItem(int32_t id)
	: Item(id) {
	this->maxStackSize = 16;
}
EggItem::~EggItem() {
}
ItemInstance* EggItem::use(ItemInstance* item, Level* level, Player* player) {
	if(!player->abilities.instabuild) {
		--item->count;
	}

	level->playSound(player, "random.bow", 0.5, 0.5 / (float)((float)(Item::random.nextFloat() * 0.4) + 0.8));
	if(!level->isClientMaybe) {
		level->addEntity(new ThrownEgg(level, player));
	}
	return item;
}
