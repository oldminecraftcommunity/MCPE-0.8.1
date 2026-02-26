#include <inventory/ContainerMenu.hpp>
#include <inventory/Container.hpp>

ContainerMenu::ContainerMenu(Container* a2, int32_t a3)
	: BaseContainerMenu(0) {
	this->container = a2;
	this->field_1C = a3;
	a2->startOpen();
}

ContainerMenu::~ContainerMenu() {
	this->container->stopOpen();
}
std::vector<ItemInstance> ContainerMenu::getItems() {
	std::vector<ItemInstance> result;
	int32_t v2 = 0;
	while(v2 < this->container->getContainerSize()) {
		ItemInstance* v5 = this->container->getItem(v2);
		result.emplace_back(v5 ? ItemInstance(*v5) : ItemInstance());
		++v2;
	}
	return result;
}
void ContainerMenu::setSlot(int32_t a2, ItemInstance* a3) {
	this->container->setItem(a2, a3);
}
bool_t ContainerMenu::tileEntityDestroyedIsInvalid(int32_t a2) {
	return this->field_1C == a2;
}
