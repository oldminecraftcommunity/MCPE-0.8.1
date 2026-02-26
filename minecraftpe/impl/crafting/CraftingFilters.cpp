#include <crafting/CraftingFilters.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>
#include <item/ItemInstance.hpp>

bool_t CraftingFilters::isStonecutterItem(const ItemInstance& a1) {
	Tile* tileClass; // r5

	tileClass = a1.tileClass;
	if(!tileClass || tileClass == Tile::lapisBlock || tileClass == Tile::furnace || tileClass == Tile::stonecutterBench || tileClass == Tile::stoneSlabHalf && a1.getAuxValue() == 2) {
		return 0;
	}
	return tileClass->material == Material::stone || tileClass->material == Material::sand;
}
