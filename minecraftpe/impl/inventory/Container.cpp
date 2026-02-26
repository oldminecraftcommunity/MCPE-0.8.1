#include <inventory/Container.hpp>

Container::~Container() {
}
std::vector<ItemInstance> Container::getSlotCopies() {
	std::vector<ItemInstance> res;
	ItemInstance v8;
	for(int32_t v2 = 0; v2 < this->getContainerSize(); ++v2) {
		ItemInstance* v5 = this->getItem(v2);
		ItemInstance* v6;
		if(v5) {
			res.emplace_back(v5);
		} else {
			res.emplace_back(v8);
		}
	}
	return res;
}
