#include <crafting/ArmorRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
static std::vector<std::string> armorShapes[4] = {
	Recipes::Shape("XXX", "X X"), Recipes::Shape("X X", "XXX", "XXX"),
	Recipes::Shape("XXX", "X X", "X X"), Recipes::Shape("X X", "X X")
};

void ArmorRecipes::addRecipes(Recipes* a1) {
	int mats[4] = {Item::leather->itemID, Item::ironIngot->itemID, Item::emerald->itemID, Item::goldIngot->itemID};
	Item* armor[4][4] = {
		{Item::helmet_cloth, Item::helmet_iron, Item::helmet_diamond, Item::helmet_gold},
		{Item::chestplate_cloth, Item::chestplate_iron, Item::chestplate_diamond, Item::chestplate_gold},
		{Item::leggings_cloth, Item::leggings_iron, Item::leggings_diamond, Item::leggings_gold},
		{Item::boots_cloth, Item::boots_iron, Item::boots_diamond, Item::boots_gold}
	};

	for(int mat = 0; mat < 4; ++mat){
		int v4 = mats[mat];
		for(int type = 0; type < 4; ++type){
			a1->addShapedRecipe(ItemInstance(armor[type][mat]), armorShapes[type], definition('X', Item::items[v4]));
		}
	}
}
