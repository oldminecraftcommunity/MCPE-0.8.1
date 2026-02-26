#pragma once
#include <item/ItemInstance.hpp>
struct ScrollingPane;
struct FlyingItem
{
	ItemInstance field_0;
	int32_t field_14;
	double field_18;
	float field_20, field_24, field_28, field_2C;
	ScrollingPane* field_30;
	int32_t field_34;

	FlyingItem();
	FlyingItem(const FlyingItem&);
};
