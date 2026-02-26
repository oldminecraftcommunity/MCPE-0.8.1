#include <crafting/ToolRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>

static Recipes::Shape _dword_D6E4DEA0[4] = {
	Recipes::Shape("XXX", " # ", " # "),
	Recipes::Shape("X", "#", "#"),
	Recipes::Shape("XX", "X#", " #"),
	Recipes::Shape("XX", " #", " #"),
};

void ToolRecipes::addRecipes(Recipes* a1) {
	int v2;				 // r11
	int v3;				 // r6
	int v4;				 // r9
	int materials[5];	 // [sp+38h] [bp-30h] BYREF
	Item* results[4][5]; // [sp+80h] [bp+18h] BYREF

	v2 = 0;
	materials[0] = Tile::wood->blockID;
	materials[1] = Tile::stoneBrick->blockID;
	materials[2] = Item::ironIngot->itemID;
	materials[3] = Item::emerald->itemID;
	materials[4] = Item::goldIngot->itemID;
	results[0][0] = Item::pickAxe_wood;
	results[0][1] = Item::pickAxe_stone;
	results[0][2] = Item::pickAxe_iron;
	results[0][3] = Item::pickAxe_emerald;
	results[0][4] = Item::pickAxe_gold;
	results[1][0] = Item::shovel_wood;
	results[1][1] = Item::shovel_stone;
	results[1][2] = Item::shovel_iron;
	results[1][3] = Item::shovel_emerald;
	results[1][4] = Item::shovel_gold;
	results[2][0] = Item::hatchet_wood;
	results[2][1] = Item::hatchet_stone;
	results[2][2] = Item::hatchet_iron;
	results[2][3] = Item::hatchet_emerald;
	results[2][4] = Item::hatchet_gold;
	results[3][0] = Item::hoe_wood;
	results[3][1] = Item::hoe_stone;
	results[3][2] = Item::hoe_iron;
	results[3][3] = Item::hoe_emerald;
	results[3][4] = Item::hoe_gold;
	do {
		v3 = 0;
		v4 = materials[v2];
		do {
			a1->addShapedRecipe(ItemInstance(results[v3][v2]), _dword_D6E4DEA0[v3].shape, v4 > 255 ? definition<Item*, Item*>('#', Item::stick, 'X', Item::items[v4]) : definition<Item*, Tile*>('#', Item::stick, 'X', Tile::tiles[v4]));
			++v3;
		} while(v3 != 4);
		++v2;
	} while(v2 != 5);
	a1->addShapedRecipe(ItemInstance(Item::shears), " #", "# ", definition<Item*>('#', Item::ironIngot) /*inlined*/);
}
