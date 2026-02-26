#include <crafting/FoodRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>

void FoodRecipes::addRecipes(Recipes* a2) {
	a2->addShapelessRecipe(ItemInstance(Item::mushroomStew), definition<Tile*, Tile*, Item*>(0, Tile::mushroom1, 0, Tile::mushroom2, 0, Item::bowl)); //definition<> is inlined
	a2->addShapedRecipe(ItemInstance(Item::beetrootSoup), "BB", "BB", "#", definition<Item*, Item*>('B', Item::beetroot, '#', Item::bowl));
	a2->addShapedRecipe(ItemInstance(Tile::melon), "MMM", "MMM", "MMM", definition<Item*>('M', Item::melon));
	a2->addShapedRecipe(ItemInstance(Item::seeds_melon), "M", definition<Item*>('M', Item::melon));
	a2->addShapedRecipe(ItemInstance(Item::seeds_pumpkin, 4), "M", definition<Tile*>('M', Tile::pumpkin));
	a2->addShapelessRecipe(ItemInstance(Item::pumpkinPie), definition<Tile*, Item*, Item*>(0, Tile::pumpkin, 0, Item::sugar, 0, Item::egg));
}
