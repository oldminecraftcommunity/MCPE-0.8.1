#pragma once
#include <item/Item.hpp>

struct DoorItem: Item
{
	struct Material* field_48;
	static void place(Level*, int32_t, int32_t, int32_t, int32_t, struct Tile*);
	DoorItem(int32_t id, Material* mat);

	virtual ~DoorItem();
	virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);

};
