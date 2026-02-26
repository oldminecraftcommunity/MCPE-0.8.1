#pragma once
#include <crafting/Recipe.hpp>

struct ShapelessRecipe: Recipe
{
	std::vector<ItemInstance> field_1C;
	std::vector<ItemInstance> field_28;

	ShapelessRecipe(std::vector<ItemInstance>& results, std::vector<ItemInstance>& ingridients); //inlined
	virtual ~ShapelessRecipe();
	virtual bool_t matches(CraftingContainer*);
	virtual int32_t getMaxCraftCount(ItemPack&);
	virtual int32_t size();
	virtual std::vector<ItemInstance>* assemble(CraftingContainer*);
	virtual std::vector<ItemInstance>* getResultItem() const;
	virtual int32_t getCraftingSize();
};
