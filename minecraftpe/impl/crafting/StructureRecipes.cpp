#include <crafting/StructureRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>

void StructureRecipes::addRecipes(Recipes* a1) {
	a1->addShapedRecipe(ItemInstance(Tile::chest), "###", "# #", "###", definition<Tile*>('#', Tile::wood));
	a1->addShapedRecipe(ItemInstance(Tile::furnace), "###", "# #", "###", definition<Tile*>('#', Tile::stoneBrick));
	a1->addShapedRecipe(ItemInstance(Tile::workBench), "##", "##", definition<Tile*>('#', Tile::wood));
	a1->addShapedRecipe(ItemInstance(Tile::stonecutterBench), "##", "##", definition<Tile*>('#', Tile::stoneBrick));
	a1->addShapedRecipe(ItemInstance(Tile::sandStone), "##", "##", definition<Tile*>('#', Tile::sand));
	a1->addShapedRecipe(ItemInstance(Tile::sandStone, 4, 2), "##", "##", definition<Tile*>('#', Tile::sandStone));
	a1->addShapedRecipe(ItemInstance(Tile::sandStone, 1, 1), "#", "#", definition<ItemInstance>('#', ItemInstance(Tile::stoneSlabHalf, 1, 1)));
	a1->addShapedRecipe(ItemInstance(Tile::stoneBrickSmooth, 4), "##", "##", definition<Tile*>('#', Tile::rock));
	a1->addShapedRecipe(ItemInstance(Tile::thinGlass, 16), "###", "###", definition<Tile*>('#', Tile::glass));
	a1->addShapedRecipe(ItemInstance(Tile::netherBrick, 1), "NN", "NN", definition<Item*>('N', Item::netherbrick));
	a1->addShapedRecipe(ItemInstance(Tile::quartzBlock, 1), "NN", "NN", definition<Item*>('N', Item::netherQuartz));
	a1->addShapedRecipe(ItemInstance(Tile::quartzBlock, 1, 1), "#", "#", definition<ItemInstance>('#', ItemInstance(Tile::stoneSlabHalf, 1, 6)));
	a1->addShapedRecipe(ItemInstance(Tile::quartzBlock, 2, 2), "#", "#", definition<ItemInstance>('#', ItemInstance(Tile::quartzBlock, 1, 0)));
}
