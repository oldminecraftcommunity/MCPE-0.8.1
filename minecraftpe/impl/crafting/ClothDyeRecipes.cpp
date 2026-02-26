#include <crafting/ClothDyeRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>

void ClothDyeRecipes::addRecipes(Recipes* a2) {
	int v2; // r9

	v2 = 0;
	do {
		a2->addShapelessRecipe(ItemInstance(Tile::cloth, 1, ~(int8_t)v2 & 0xF), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, v2), 0, ItemInstance(Item::items[Tile::cloth->blockID], 1, 0)));
		++v2;
	} while(v2 != 16);

	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 11), definition<Tile*>(0, Tile::flower));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 1), definition<Item*>(0, Item::beetroot));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 3, 15), definition<Item*>(0, Item::bone));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 9), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 1), 0, ItemInstance(Item::dye_powder, 1, 15)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 14), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 1), 0, ItemInstance(Item::dye_powder, 1, 11)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 10), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 2), 0, ItemInstance(Item::dye_powder, 1, 15)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 8), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 0), 0, ItemInstance(Item::dye_powder, 1, 15)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 7), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 8), 0, ItemInstance(Item::dye_powder, 1, 15)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 3, 7), definition<ItemInstance, ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 0), 0, ItemInstance(Item::dye_powder, 1, 15), 0, ItemInstance(Item::dye_powder, 1, 15)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 3), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 0), 0, ItemInstance(Item::dye_powder, 1, 14)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 3, 3), definition<ItemInstance, ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 0), 0, ItemInstance(Item::dye_powder, 1, 1), 0, ItemInstance(Item::dye_powder, 1, 11)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 12), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 4), 0, ItemInstance(Item::dye_powder, 1, 15)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 6), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 4), 0, ItemInstance(Item::dye_powder, 1, 2)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 5), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 4), 0, ItemInstance(Item::dye_powder, 1, 1)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 2, 13), definition<ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 5), 0, ItemInstance(Item::dye_powder, 1, 9)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 3, 13), definition<ItemInstance, ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 4), 0, ItemInstance(Item::dye_powder, 1, 1), 0, ItemInstance(Item::dye_powder, 1, 9)));
	a2->addShapelessRecipe(ItemInstance(Item::dye_powder, 4, 13), definition<ItemInstance, ItemInstance, ItemInstance, ItemInstance>(0, ItemInstance(Item::dye_powder, 1, 4), 0, ItemInstance(Item::dye_powder, 1, 1), 0, ItemInstance(Item::dye_powder, 1, 1), 0, ItemInstance(Item::dye_powder, 1, 15)));
}
