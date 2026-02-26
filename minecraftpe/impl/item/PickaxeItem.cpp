#include <item/PickaxeItem.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

PickaxeItem::PickaxeItem(int32_t a2, const Item::Tier& a3)
	: DiggerItem(a2, a3) {
	this->damageAgainstEntity = a3.damageAgainstEntity + 2;
	std::vector<Tile*> tiles;
	tiles.push_back(Tile::stoneBrick);
	tiles.push_back(Tile::stoneSlab);
	tiles.push_back(Tile::stoneSlabHalf);
	tiles.push_back(Tile::rock);
	tiles.push_back(Tile::sandStone);
	tiles.push_back(Tile::mossStone);
	tiles.push_back(Tile::ironOre);
	tiles.push_back(Tile::ironBlock);
	tiles.push_back(Tile::coalOre);
	tiles.push_back(Tile::goldBlock);
	tiles.push_back(Tile::goldOre);
	tiles.push_back(Tile::emeraldOre);
	tiles.push_back(Tile::emeraldBlock);
	tiles.push_back(Tile::ice);
	tiles.push_back(Tile::lapisOre);
	tiles.push_back(Tile::lapisBlock);
	tiles.push_back(Tile::redStoneOre);
	tiles.push_back(Tile::redStoneOre_lit);
	this->setTiles(tiles);
}

PickaxeItem::~PickaxeItem() {
}
float PickaxeItem::getDestroySpeed(ItemInstance* a2, Tile* a3) {
	if(a3 && (a3->material == Material::metal || a3->material == Material::stone)) {
		return this->efficiencyMultiplier;
	} else {
		return DiggerItem::getDestroySpeed(a2, a3);
	}
}
bool_t PickaxeItem::canDestroySpecial(const Tile* a2) {
	if(a2 == Tile::obsidian || a2 == Tile::glowingObsidian) {
		return this->tier->level == 3;
	}

	if(a2 == Tile::emeraldBlock || a2 == Tile::emeraldOre || a2 == Tile::goldBlock || a2 == Tile::goldOre) {
		goto LABEL_8;
	}
	if(a2 != Tile::ironBlock && a2 != Tile::ironOre && a2 != Tile::lapisBlock && a2 != Tile::lapisOre) {
		if(a2 != Tile::redStoneOre && a2 != Tile::redStoneOre_lit) {
			if(a2->material == Material::stone) {
				return 1;
			}
			return a2->material == Material::metal;
		}
LABEL_8:
		return !(this->tier->level <= 1);
	}
	return !(this->tier->level <= 0);
}
