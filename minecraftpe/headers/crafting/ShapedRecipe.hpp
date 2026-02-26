#pragma once
#include <crafting/Recipe.hpp>

struct ShapedRecipe: Recipe
{
	int32_t width, height;
	ItemInstance* field_24;
	std::vector<ItemInstance> field_28;
	ShapedRecipe(int32_t w, int32_t h, ItemInstance* f24, const std::vector<ItemInstance>& f28); //inlined
	bool_t matches(CraftingContainer*, int32_t, int32_t, bool_t);

	virtual ~ShapedRecipe();
	virtual bool_t matches(CraftingContainer*);
	virtual int32_t getMaxCraftCount(ItemPack&);
	virtual int32_t size();
	virtual std::vector<ItemInstance>* assemble(CraftingContainer*);
	virtual const std::vector<ItemInstance>* getResultItem() const;
	virtual int32_t getCraftingSize();
	virtual std::vector<ItemInstance> getItems() ; //TODO check return type
};
