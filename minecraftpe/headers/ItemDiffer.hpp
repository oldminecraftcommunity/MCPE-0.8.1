#pragma once
#include <item/ItemInstance.hpp>
#include <vector>

struct ItemInstance;
struct ItemDiffer
{
	int32_t len, field_4;
	ItemInstance* items;

	ItemDiffer(const std::vector<const ItemInstance*>& a2) {
		this->len = a2.size();
		this->items = new ItemInstance[this->len];
		for (int32_t i = 0; i < this->len; ++i) {
			if (a2[i]) {
				this->items[i] = *a2[i];
			} else {
				this->items[i].setNull();
			}
		}
	}
	void getDiff(const std::vector<const ItemInstance*>& a2, std::vector<int32_t>& a3) {
		int32_t len = a2.size();
		if (len < this->len) {
			len = this->len;
		}
		for (int32_t i = 0; i < len; ++i) {
			if (!ItemInstance::matchesNulls(&this->items[i], a2[i])) {
				a3.push_back(i);
			}
		}
	}

};
