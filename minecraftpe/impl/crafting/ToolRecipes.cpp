#include <crafting/ToolRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>

static std::vector<std::string> shapes[4] = {
	Recipes::Shape("XXX", " # ", " # "),
	Recipes::Shape("X", "#", "#"),
	Recipes::Shape("XX", "X#", " #"),
	Recipes::Shape("XX", " #", " #"),
};

void ToolRecipes::addRecipes(Recipes* a1) {
	int materials[5] = {Tile::wood->blockID, Tile::stoneBrick->blockID, Item::ironIngot->itemID, Item::emerald->itemID, Item::goldIngot->itemID};
	Item* results[4][5] = {
		{Item::pickAxe_wood, Item::pickAxe_stone, Item::pickAxe_iron, Item::pickAxe_emerald, Item::pickAxe_gold},
		{Item::shovel_wood, Item::shovel_stone, Item::shovel_iron, Item::shovel_emerald, Item::shovel_gold},
		{Item::hatchet_wood, Item::hatchet_stone, Item::hatchet_iron, Item::hatchet_emerald, Item::hatchet_gold},
		{Item::hoe_wood, Item::hoe_stone, Item::hoe_iron, Item::hoe_emerald, Item::hoe_gold}
	};

	for(int mat = 0; mat < 5; ++mat){
		int matid = materials[mat];
		for(int tool = 0; tool < 4; ++tool){
			a1->addShapedRecipe(
				ItemInstance(results[tool][mat]),
				shapes[tool],
				matid > 255 ? definition<Item*, Item*>('#', Item::stick, 'X', Item::items[matid]) : definition<Item*, Tile*>('#', Item::stick, 'X', Tile::tiles[matid])
			);
		}
	}
	a1->addShapedRecipe(ItemInstance(Item::shears), " #", "# ", definition<Item*>('#', Item::ironIngot));
}
