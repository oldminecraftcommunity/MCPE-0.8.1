#include <entity/MinecartRideable.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>

MinecartRideable::MinecartRideable(Level* a2) : Minecart(a2){

}
MinecartRideable::MinecartRideable(Level* a2, float x, float y, float z) : Minecart(a2, x, y, z){

}

MinecartRideable::~MinecartRideable() {
}
bool_t MinecartRideable::interactWithPlayer(Player* a2) {
	if(this->rider && this->rider->isPlayer() && this->rider == a2) {
		return 1;
	}

	if(!this->rider || this->rider == a2) {
		if(!this->level->isClientMaybe) {
			a2->ride(this);
		}
		return 1;
	}
	return 0;
}
int32_t MinecartRideable::getType() {
	return 0;
}
