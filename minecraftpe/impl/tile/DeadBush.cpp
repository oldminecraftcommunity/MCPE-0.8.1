#include <tile/DeadBush.hpp>
#include <level/Level.hpp>
#include <entity/Player.hpp>
#include <item/Item.hpp>

DeadBush::DeadBush(int32_t id, const std::string& name)
	: Bush(id, name) {
	this->textureUV = this->getTextureUVCoordinateSet(name, 1);
}

DeadBush::~DeadBush() {
}
int32_t DeadBush::getResource(int32_t, Random*) {
	return -1;
}
void DeadBush::playerDestroy(Level* level, Player* player, int32_t x, int32_t y, int32_t z, int32_t a7) {
	if(!level->isClientMaybe && player->getSelectedItem()) {
		ItemInstance* selected = player->getSelectedItem(); //2 calls
		if(selected->getId() == Item::shears->itemID) {
			this->popResource(level, x, y, z, ItemInstance(Tile::deadBush, 1, a7));
		} else {
			this->playerDestroy(level, player, x, y, z, a7);
		}
	}
}
bool_t DeadBush::mayPlaceOn(int32_t a2) {
	return a2 == Tile::sand->blockID;
}
