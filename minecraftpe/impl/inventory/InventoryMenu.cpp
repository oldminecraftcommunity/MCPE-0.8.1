#include <inventory/InventoryMenu.hpp>
#include <inventory/Container.hpp>

InventoryMenu::InventoryMenu(Container* a2)
	: BaseContainerMenu(0) {
	this->linkedContainer = a2;
}

InventoryMenu::~InventoryMenu() {
}
std::vector<ItemInstance> InventoryMenu::getItems() {
	std::vector<ItemInstance> result;
	for(int32_t v4 = 9; v4 < this->linkedContainer->getContainerSize(); ++v4) {
		ItemInstance* v5 = this->linkedContainer->getItem(v4);
		result.emplace_back(v5 ? ItemInstance(*v5) : ItemInstance());
	}
	return result;
}
void InventoryMenu::setSlot(int32_t a2, ItemInstance* a3) {
	this->linkedContainer->setItem(a2 + 9, a3);
}
bool_t InventoryMenu::tileEntityDestroyedIsInvalid(int32_t) {
	return 0;
}
