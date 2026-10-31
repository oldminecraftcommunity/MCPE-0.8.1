#include <crafting/OreRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>
struct Entry
{
	Tile* result;
	ItemInstance material;
};
void OreRecipes::addRecipes(Recipes* a1) {
	Entry v13[] = {
		{Tile::goldBlock, ItemInstance(Item::goldIngot, 9)},
		{Tile::ironBlock, ItemInstance(Item::ironIngot, 9)},
		{Tile::emeraldBlock, ItemInstance(Item::emerald, 9)},
		{Tile::lapisBlock, ItemInstance(Item::dye_powder, 9, 4)},
		{Tile::hayBlock, ItemInstance(Item::wheat, 9)},
		{Tile::coalBlock, ItemInstance(Item::coal, 9)}
	};

	for(int v2 = 0; v2 < 6; ++v2) {
		Tile* a2 = v13[v2].result;
		a1->addShapedRecipe(ItemInstance(a2), "###", "###", "###", definition<ItemInstance>('#', ItemInstance(v13[v2].material)));
		a1->addShapedRecipe(ItemInstance(v13[v2].material) /*v9 reuse*/, "#", definition<Tile*>('#', a2));
	}
}
