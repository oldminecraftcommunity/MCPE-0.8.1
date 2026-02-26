#include <item/ShovelItem.hpp>
#include <tile/Tile.hpp>

ShovelItem::ShovelItem(int32_t a2, const Item::Tier& tier)
	: DiggerItem(a2, tier) {
	this->damageAgainstEntity = tier.damageAgainstEntity + 1;
	std::vector<Tile*> v9;
	v9.push_back(Tile::grass);
	v9.push_back(Tile::dirt);
	v9.push_back(Tile::sand);
	v9.push_back(Tile::gravel);
	v9.push_back(Tile::topSnow);
	v9.push_back(Tile::snow);
	v9.push_back(Tile::clay);
	v9.push_back(Tile::farmland);
	this->setTiles(v9);
}

ShovelItem::~ShovelItem() {
}
bool_t ShovelItem::canDestroySpecial(const Tile* a2) {
	return a2 == Tile::topSnow || a2 == Tile::snow;
}
