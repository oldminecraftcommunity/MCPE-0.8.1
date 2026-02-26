#pragma once
#include <crafting/ItemPack.hpp>

struct CraftingContainer;
struct Recipe
{
	static int32_t SIZE_2X2, SIZE_3X3;

	ItemPack items;

	Recipe();
	static bool_t isAnyAuxValue(int32_t id);

	virtual ~Recipe();
	virtual bool_t matches(CraftingContainer*) = 0;
	virtual ItemPack* getItemPack();
	virtual int32_t getMaxCraftCount(ItemPack&) = 0;
	virtual int32_t size() = 0;
	virtual std::vector<ItemInstance>* assemble(CraftingContainer*) = 0;
	virtual const std::vector<ItemInstance>* getResultItem() const = 0;
	virtual int32_t getCraftingSize() = 0;
};
