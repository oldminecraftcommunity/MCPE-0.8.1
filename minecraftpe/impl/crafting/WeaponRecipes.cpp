#include <crafting/WeaponRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>
static Recipes::Shape _dword_D6E4DEF8("X", "X", "#");
void WeaponRecipes::addRecipes(Recipes* a1) {
	int v2;			  // r6
	int v3;			  // r7
	int mats[5];	  // [sp+34h] [bp-84h] BYREF
	Item* results[5]; // [sp+48h] [bp-70h] BYREF

	v2 = 0;
	mats[0] = Tile::wood->blockID;
	mats[1] = Tile::stoneBrick->blockID;
	mats[2] = Item::ironIngot->itemID;
	mats[3] = Item::emerald->itemID;
	mats[4] = Item::goldIngot->itemID;
	results[0] = Item::sword_wood;
	results[1] = Item::sword_stone;
	results[2] = Item::sword_iron;
	results[3] = Item::sword_emerald;
	results[4] = Item::sword_gold;
	do {
		v3 = mats[v2];
		a1->addShapedRecipe(ItemInstance(results[v2]), _dword_D6E4DEF8.shape, /*inlined*/ v3 <= 255 ? definition<Item*, Tile*>('#', Item::stick, 'X', Tile::tiles[v3]) : definition<Item*, Item*>('#', Item::stick, 'X', Item::items[v3]));
		++v2;

	} while(v2 != 5);

	a1->addShapedRecipe(ItemInstance(Item::bow, 1), " #X", "# X", " #X", definition<Item*, Item*>('X', Item::string, '#', Item::stick) /*inlined*/);
	a1->addShapedRecipe(ItemInstance(Item::arrow, 4), "X", "#", "Y", definition<Item*, Item*, Item*>('Y', Item::feather, 'X', Item::flint, '#', Item::stick));
}
