#include <item/HatchetItem.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

HatchetItem::HatchetItem(int32_t a2, const Item::Tier& a3)
	: DiggerItem(a2, a3) {
	this->damageAgainstEntity = a3.damageAgainstEntity + 3;
	std::vector<Tile*> tiles;
	tiles.push_back(Tile::wood);
	tiles.push_back(Tile::bookshelf);
	tiles.push_back(Tile::treeTrunk);
	tiles.push_back(Tile::chest);
	tiles.push_back(Tile::woodSlab);
	tiles.push_back(Tile::woodSlabHalf);
	this->setTiles(tiles);
}

HatchetItem::~HatchetItem() {
}
float HatchetItem::getDestroySpeed(ItemInstance* a2, Tile* a3) {
	if(a3 && a3->material == Material::wood) {
		return this->efficiencyMultiplier;
	}
	return DiggerItem::getDestroySpeed(a2, a3);
}
