#include <tile/LightGemTile.hpp>
#include <util/Random.hpp>
#include <item/Item.hpp>

LightGemTile::LightGemTile(int32_t a2, const std::string& a3, const struct Material* a4)
	: Tile(a2, a3, a4) {
	this->field_5C = 255;
}

LightGemTile::~LightGemTile() {
}
int32_t LightGemTile::getResource(int32_t, Random*) {
	return Item::yellowDust->itemID;
}
int32_t LightGemTile::getResourceCount(Random* a2) {
	return a2->genrand_int32() % 3 + 2;
}
