#include <ItemDiffer.hpp>
#include <item/ItemInstance.hpp>

ItemDiffer::ItemDiffer(const std::vector<const ItemInstance*>& a2) {
	this->len = a2.size();
	this->items = new ItemInstance[this->len];
	for(int32_t i = 0; i < this->len; ++i) {
		if(a2[i]) {
			this->items[i] = *a2[i];
		} else {
			this->items[i].setNull();
		}
	}
}
void ItemDiffer::getDiff(const std::vector<const ItemInstance*>& a2, std::vector<int32_t>& a3) {
	int32_t len = a2.size();
	if(len < this->len) {
		len = this->len;
	}
	for(int32_t i = 0; i < len; ++i) {
		if(ItemInstance::matchesNulls(&this->items[i], a2[i])) {
			a3.emplace_back(i);
		}
	}
}
