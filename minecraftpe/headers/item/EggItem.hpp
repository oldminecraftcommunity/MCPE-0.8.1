#pragma once
#include <item/Item.hpp>
#include <entity/Player.hpp>
#include <entity/ThrownEgg.hpp>
#include <level/Level.hpp>

struct EggItem: Item
{
	EggItem(int32_t id) :
			Item(id) {
		this->maxStackSize = 16;
	}
	virtual ~EggItem() {
	}
	virtual ItemInstance* use(ItemInstance* item, Level* level, Player* player) {
		if (!player->abilities.instabuild) {
			--item->count;
		}
		level->playSound(player, "random.bow", 0.5, 0.5 / (float) (((float) ((Item::random.nextFloat() * 0.4)) + 0.8)));
		if (!level->isClient) {
			level->addEntity(new ThrownEgg(level, player));
		}
		return item;
	}
};
