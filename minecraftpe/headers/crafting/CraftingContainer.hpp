#pragma once
#include <_types.h>
#include <item/ItemInstance.hpp>

struct CraftingContainer
{
	//TODO find out the structure of this thing
	void* field_0;
	int field_4, field_8, field_C, field_10, field_14;
	ItemInstance* getItem(int32_t, int32_t); //TODO check return type
};
