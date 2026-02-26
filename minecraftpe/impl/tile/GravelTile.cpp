#include <tile/GravelTile.hpp>
#include <item/Item.hpp>

GravelTile::GravelTile(int32_t id, const std::string& s)
	: HeavyTile(id, s) {
}
GravelTile::~GravelTile() {
}
int GravelTile::getResource(int32_t a2, Random* a3) {
	if(a3->genrand_int32() % 0xa) return this->blockID;
	return Item::flint->itemID;
}
