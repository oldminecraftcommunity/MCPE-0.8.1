#pragma once
#include <_types.h>
#include <vector>
#include <string>
#include <item/ItemInstance.hpp>

struct Recipe;
struct Item;
struct Tile;
struct Recipes
{
	struct Shape
	{
		std::vector<std::string> shape;

		Shape(const std::string&);
		Shape(const std::string&, const std::string&);
		Shape(const std::string&, const std::string&, const std::string&);
	};

	struct Type
	{
		Item* item;
		Tile* tile;
		ItemInstance itemInstance;
		char_t chr;
		char field_1D, field_1E, field_1F;

		Type(const Recipes::Type&);
		Type(char_t, Item*);
		Type(char_t, const ItemInstance&);
		Type(char_t, Tile*);
	};
	static Recipes* instance;
	std::vector<Recipe*> recipes;
	Recipes();
	void addShapedRecipe(const ItemInstance&, const std::string&, const std::string&, const std::string&, const std::vector<Recipes::Type>&);
	void addShapedRecipe(const ItemInstance&, const std::string&, const std::string&, const std::vector<Recipes::Type>&);
	void addShapedRecipe(const ItemInstance&, const std::string&, const std::vector<Recipes::Type>&);
	void addShapedRecipe(const ItemInstance&, const std::vector<std::string>, const std::vector<Recipes::Type>&); //TODO last arg type might be slightly different
	void addShapedRecipe(const std::vector<ItemInstance>&, const std::vector<std::string, std::allocator<std::string>>, const std::vector<Recipes::Type>&); //TODO check signature
	void addShapelessRecipe(const ItemInstance&, const std::vector<Recipes::Type>&);
	static Recipes* getInstance();
	Recipe* getRecipeFor(const ItemInstance&);
	std::vector<Recipe*>* getRecipes(); //TODO prob different type
	static void teardownRecipes();

	~Recipes();
};

#define _d_arg(n) char a##n, T##n b##n
#define _d_emplc(n) ret.emplace_back(Recipes::Type(a##n, b##n));
template<typename T0>
std::vector<Recipes::Type> definition(_d_arg(0)) {
	std::vector<Recipes::Type> ret;
	_d_emplc(0);
	return ret;
}
template<typename T0, typename T1>
std::vector<Recipes::Type> definition(_d_arg(0), _d_arg(1)) {
	std::vector<Recipes::Type> ret;
	_d_emplc(0);
	_d_emplc(1);
	return ret;
}
template<typename T0, typename T1, typename T2>
std::vector<Recipes::Type> definition(_d_arg(0), _d_arg(1), _d_arg(2)) {
	std::vector<Recipes::Type> ret;
	_d_emplc(0);
	_d_emplc(1);
	_d_emplc(2);
	return ret;
}

//inlined
template<typename T0, typename T1, typename T2, typename T3>
std::vector<Recipes::Type> definition(_d_arg(0), _d_arg(1), _d_arg(2), _d_arg(3)) {
	std::vector<Recipes::Type> ret;
	_d_emplc(0);
	_d_emplc(1);
	_d_emplc(2);
	_d_emplc(3);
	return ret;
}
