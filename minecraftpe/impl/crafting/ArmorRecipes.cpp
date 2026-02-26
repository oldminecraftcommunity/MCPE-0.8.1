#include <crafting/ArmorRecipes.hpp>
#include <crafting/Recipes.hpp>
#include <item/Item.hpp>
static Recipes::Shape _dword_D6E4DD70[4] = {Recipes::Shape("XXX", "X X"), Recipes::Shape("X X", "XXX", "XXX"), Recipes::Shape("XXX", "X X", "X X"), Recipes::Shape("X X", "X X")};

void ArmorRecipes::addRecipes(Recipes* a1) {
	int v2;			 // r5
	int v3;			 // r6
	int v4;			 // r10
	Item* v5;		 // r2
	int v7[4];		 // [sp+Ch] [bp-ACh] BYREF
	Item* v10[4][4]; // [sp+50h] [bp-68h] BYREF

	v2 = 0;
	v7[0] = Item::leather->itemID;
	v7[1] = Item::ironIngot->itemID;
	v7[2] = Item::emerald->itemID;
	v7[3] = Item::goldIngot->itemID;
	v10[0][0] = Item::helmet_cloth;
	v10[0][1] = Item::helmet_iron;
	v10[0][2] = Item::helmet_diamond;
	v10[0][3] = Item::helmet_gold;
	v10[1][0] = Item::chestplate_cloth;
	v10[1][1] = Item::chestplate_iron;
	v10[1][2] = Item::chestplate_diamond;
	v10[1][3] = Item::chestplate_gold;
	v10[2][0] = Item::leggings_cloth;
	v10[2][1] = Item::leggings_iron;
	v10[2][2] = Item::leggings_diamond;
	v10[2][3] = Item::leggings_gold;
	v10[3][0] = Item::boots_cloth;
	v10[3][1] = Item::boots_iron;
	v10[3][2] = Item::boots_diamond;
	v10[3][3] = Item::boots_gold;
	do {
		v3 = 0;
		v4 = v7[v2];
		do {
			ItemInstance v8(v10[v3][v2]);
			v5 = Item::items[v4];
			std::vector<Recipes::Type> v6;
			v6.emplace_back(Recipes::Type('X', v5)); //inlined
			a1->addShapedRecipe(v8, _dword_D6E4DD70[v3++].shape, v6);
		} while(v3 != 4);
		++v2;
	} while(v2 != 4);
}
