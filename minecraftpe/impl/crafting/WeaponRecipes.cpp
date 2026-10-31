#include <crafting/WeaponRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>
static std::vector<std::string> swordShape = Recipes::Shape("X", "X", "#");
void WeaponRecipes::addRecipes(Recipes* a1) {
	int mats[5] = {Tile::wood->blockID, Tile::stoneBrick->blockID, Item::ironIngot->itemID, Item::emerald->itemID, Item::goldIngot->itemID};
	Item* results[5] = {Item::sword_wood, Item::sword_stone, Item::sword_iron, Item::sword_emerald, Item::sword_gold};

	for(int v2 = 0; v2 < 5; ++v2) {
		int v3 = mats[v2];
		a1->addShapedRecipe(ItemInstance(results[v2]), swordShape, v3 <= 255 ? definition<Item*, Tile*>('#', Item::stick, 'X', Tile::tiles[v3]) : definition<Item*, Item*>('#', Item::stick, 'X', Item::items[v3]));
	}

	a1->addShapedRecipe(ItemInstance(Item::bow, 1), " #X", "# X", " #X", definition<Item*, Item*>('X', Item::string, '#', Item::stick));
	a1->addShapedRecipe(ItemInstance(Item::arrow, 4), "X", "#", "Y", definition<Item*, Item*, Item*>('Y', Item::feather, 'X', Item::flint, '#', Item::stick));
}
