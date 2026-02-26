#pragma once
#include <item/ItemInstance.hpp>
#include <vector>

struct Recipe;
struct CItem
{
	struct ReqItem
	{
		ItemInstance item;
		int32_t field_14;
		ReqItem(ItemInstance& item, int count);
		ReqItem(const CItem::ReqItem&);
	};

	ItemInstance field_0;
	Recipe* recipe;
	std::string field_18, field_1C;
	int32_t field_20, field_24;
	std::vector<CItem::ReqItem> field_28;
	int8_t field_34, field_35, field_36, field_37;

	CItem(const ItemInstance&, Recipe*, const std::string&);
	~CItem();
};
