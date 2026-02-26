#include <crafting/ItemPack.hpp>
#include <item/ItemInstance.hpp>
#include <crafting/Recipe.hpp>

void ItemPack::add(int32_t id, int32_t cnt) {
	auto&& p = this->items.find(id);
	if(p == this->items.end()) {
		this->items.insert({id, cnt});
	} else {
		p->second += cnt;
	}
}
int32_t ItemPack::getCount(int32_t a2) {
	auto&& v3 = this->items.find(a2);
	if(v3 == this->items.end()) return 0;
	return v3->second;
}
int32_t ItemPack::getIdForItemInstance(const ItemInstance* a1) {
	int id; // r0
	bool_t v3; // r5
	int v4; // r6
	int aux; // r0

	id = a1->getId();
	v3 = Recipe::isAnyAuxValue(id) || a1->isDamageableItem();
	v4 = a1->getId() << 9;
	if(v3) {
		aux = -1;
	} else {
		aux = a1->getAuxValue();
	}
	return v4 + aux;
}
int32_t ItemPack::getIdForItemInstanceAnyAux(const ItemInstance* a1) {
	return (a1->getId() << 9) - 1;
}
ItemInstance ItemPack::getItemInstanceForId(int32_t a2) {
	int v2; // r2

	v2 = a2 + 256;
	if(a2 + 256 < 0) {
		v2 = a2 + 767;
	}
	return ItemInstance(v2 >> 9, 1, (((int16_t)a2 + 256) & 0x1ff) - 256);
}
std::vector<ItemInstance> ItemPack::getItemInstances() {
	std::vector<ItemInstance> result;
	for(auto&& p: this->items) {
		ItemInstance v9 = ItemPack::getItemInstanceForId(p.first);
		v9.count = p.second;
		result.emplace_back(v9);
	}
	return result;
}
int32_t ItemPack::getMaxMultipliesOf(ItemPack& a2) {
	int32_t v3 = 99;
	for(auto&& v4 = a2.items.begin(); v4 != a2.items.end(); ++v4) {
		auto&& v7 = this->items.find(v4->first);
		if(v7 == this->items.end()) {
			return 0;
		}
		int32_t v8 = v4->second;
		if(!v8) return 0;
		int32_t v9 = v7->second / v8;
		if(!v9) return 0;
		if(v3 >= v9) v3 = v9;
	}
	return v3;
}
void ItemPack::print() {
}
