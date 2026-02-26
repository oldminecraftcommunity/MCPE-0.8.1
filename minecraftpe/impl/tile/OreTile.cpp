#include <tile/OreTile.hpp>
#include <util/Random.hpp>
#include <item/Item.hpp>
#include <tile/material/Material.hpp>

OreTile::OreTile(int32_t a2, const std::string& a3) : Tile(a2, a3, Material::stone){

}

OreTile::~OreTile() {
}
int32_t OreTile::getResource(int32_t a2, Random* a3) {
	int32_t result; // r0
	Item* v4;
	result = this->blockID;
	if(result == Tile::coalOre->blockID) {
		v4 = Item::coal;
	} else if(result == Tile::emeraldOre->blockID) {
		v4 = Item::emerald;
	} else {
		if(result != Tile::lapisOre->blockID) {
			return result;
		}
		v4 = Item::dye_powder;
	}
	return v4->itemID;
}
int32_t OreTile::getResourceCount(Random* a2) {
	if(this->blockID == Tile::lapisOre->blockID) {
		return a2->genrand_int32() % 5 + 4;
	} else {
		return 1;
	}
}
int32_t OreTile::getSpawnResourcesAuxValue(int32_t a2) {
	if(this->blockID == Tile::lapisOre->blockID) {
		return 4;
	} else {
		return 0;
	}
}
