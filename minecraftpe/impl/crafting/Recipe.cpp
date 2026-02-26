#include <crafting/Recipe.hpp>
#include <tile/Tile.hpp>
int32_t Recipe::SIZE_2X2 = 0;
int32_t Recipe::SIZE_3X3 = 1;

Recipe::Recipe() {
}
bool_t Recipe::isAnyAuxValue(int32_t id) {
	return id <= 255 && id != Tile::cloth->blockID && id != Tile::stoneSlabHalf->blockID && id != Tile::sandStone->blockID && id != Tile::treeTrunk->blockID && id != Tile::wood->blockID;
}

Recipe::~Recipe() {
}
ItemPack* Recipe::getItemPack() {
	return &this->items;
}
