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

	struct Type
	{
		Item* item;
		Tile* tile;
		ItemInstance itemInstance;
		char_t chr;

		Type(const Recipes::Type& a2) = default;
		Type(char_t a2, Item* a3) : item(a3), tile(0), chr(a2) {
		}
		Type(char_t a2, const ItemInstance& a3)
			: item(0), tile(0), chr(a2), itemInstance(a3) {
		}
		Type(char_t a2, Tile* a3) : tile(a3), item(0), chr(a2) {
		}
	};

	static std::vector<std::string> Shape(const std::string&);
	static std::vector<std::string> Shape(const std::string&, const std::string&);
	static std::vector<std::string> Shape(const std::string&, const std::string&, const std::string&);

	static Recipes* instance;
	std::vector<Recipe*> recipes;
	Recipes();
	void addShapedRecipe(const ItemInstance&, const std::string&, const std::string&, const std::string&, const std::vector<Recipes::Type>&);
	void addShapedRecipe(const ItemInstance&, const std::string&, const std::string&, const std::vector<Recipes::Type>&);
	void addShapedRecipe(const ItemInstance&, const std::string&, const std::vector<Recipes::Type>&);
	void addShapedRecipe(const ItemInstance&, const std::vector<std::string>&, const std::vector<Recipes::Type>&);
	void addShapedRecipe(const std::vector<ItemInstance>&, const std::vector<std::string>&, const std::vector<Recipes::Type>&);
	void addShapelessRecipe(const ItemInstance&, const std::vector<Recipes::Type>&);
	static Recipes* getInstance();
	Recipe* getRecipeFor(const ItemInstance&);
	std::vector<Recipe*>* getRecipes(); //TODO prob different type
	static void teardownRecipes();

	~Recipes();
};

#define _d_arg(n) char a##n, T##n b##n
#define _d_emplc(n) ret.push_back(Recipes::Type(a##n, b##n));
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
