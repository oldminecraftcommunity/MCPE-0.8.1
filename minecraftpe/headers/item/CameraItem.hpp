#pragma once
#include <item/Item.hpp>

struct CameraItem: Item
{
	CameraItem(int32_t);
	virtual ~CameraItem();
	virtual ItemInstance* use(ItemInstance*, Level*, Player*);
};
