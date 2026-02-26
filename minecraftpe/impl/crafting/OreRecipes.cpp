#include <crafting/OreRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>

void OreRecipes::addRecipes(Recipes* a1) {
	int v2; // r6
	int v3; // r1
	struct
	{
		Tile* result;
		ItemInstance material;
	} v13[] = {{Tile::goldBlock, ItemInstance(Item::goldIngot, 9)}, {Tile::ironBlock, ItemInstance(Item::ironIngot, 9)}, {Tile::emeraldBlock, ItemInstance(Item::emerald, 9)}, {Tile::lapisBlock, ItemInstance(Item::dye_powder, 9, 4)}, {Tile::hayBlock, ItemInstance(Item::wheat, 9)}, {Tile::coalBlock, ItemInstance(Item::coal, 9)}};
	v2 = 0;
	do {
		v3 = v2++;
		Tile* a2 = v13[v3].result;
		a1->addShapedRecipe(ItemInstance(a2), "###", "###", "###", definition<ItemInstance>('#', ItemInstance(v13[v3].material)) /*inlined, does copy of ItemInstance*/);
		a1->addShapedRecipe(ItemInstance(v13[v3].material) /*v9 reuse*/, "#", definition<Tile*>('#', a2) /*inlined*/);
	} while(v2 != 6);
}
