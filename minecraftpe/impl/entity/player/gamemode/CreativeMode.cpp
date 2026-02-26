#include <entity/player/gamemode/CreativeMode.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <entity/player/Abilities.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>

CreativeMode::CreativeMode(Minecraft* a2)
	: GameMode(a2) {
}
void CreativeMode::creativeDestroyBlock(int32_t x, int32_t y, int32_t z, int32_t side) {
	this->minecraft->level->extinguishFire(x, y, z, side);
	this->destroyBlock(x, y, z, side);
}

CreativeMode::~CreativeMode() {
}
void CreativeMode::startDestroyBlock(int32_t x, int32_t y, int32_t z, int32_t side) {
	if(!this->minecraft->player->getCarriedItem() || Item::bow != this->minecraft->player->getCarriedItem()->itemClass || !Item::bow) {
		this->creativeDestroyBlock(x, y, z, side);
		this->delay = 10;
	}
}
void CreativeMode::continueDestroyBlock(int32_t x, int32_t y, int32_t z, int32_t side) {
	if(this->delay - 1 <= 0) {
		this->delay = 10;
		this->creativeDestroyBlock(x, y, z, side);
	} else {
		--this->delay;
	}
}
void CreativeMode::stopDestroyBlock() {
}
bool_t CreativeMode::isCreativeType() {
	return 1;
}
void CreativeMode::initAbilities(Abilities& a2) {
	a2.mayfly = 1;
	a2.instabuild = 1;
	a2.invulnerable = 1;
}
void CreativeMode::releaseUsingItem(Player* a2) {
	Item* itemClass; // r6

	if(a2->getCarriedItem()) {
		itemClass = a2->getCarriedItem()->itemClass;
		int32_t v5 = a2->getAuxData();
		GameMode::releaseUsingItem(a2);
		if(a2->getCarriedItem()) {
			if(itemClass == a2->getCarriedItem()->itemClass) {
				if(itemClass) {
					a2->getCarriedItem()->setAuxValue(v5);
				}
			}
		}
	} else {
		GameMode::releaseUsingItem(a2);
	}
}
