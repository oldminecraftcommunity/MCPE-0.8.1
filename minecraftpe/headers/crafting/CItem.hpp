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
		ReqItem(ItemInstance& item, int count)
			: item(item) {
			this->field_14 = count;
		}
		ReqItem(const CItem::ReqItem& a2)
			: item(a2.item) {
			this->field_14 = a2.field_14;
		}
	};

	ItemInstance field_0;
	Recipe* recipe;
	std::string field_18, field_1C;
	int32_t field_20, field_24;
	std::vector<CItem::ReqItem> field_28;
	bool field_34;

	CItem(const ItemInstance& a2, Recipe* a3, const std::string& a4)
		: field_0(a2) {
		this->recipe = a3;
		this->field_18 = a4;
		this->field_1C = a4;
		this->field_20 = 0;
		this->field_24 = 0;
		this->field_34 = 0;
	}
	~CItem(){}
};
