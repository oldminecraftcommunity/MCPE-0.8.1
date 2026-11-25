#include <inventory/BaseContainerMenu.hpp>
#include <inventory/IContainerListener.hpp>
#include <item/ItemInstance.hpp>

BaseContainerMenu::BaseContainerMenu(int32_t a2) {
	this->containerType = a2;
	this->containerId = -1;
	this->containerListener = 0;
}
void BaseContainerMenu::broadcastChanges() {
	if(this->containerListener) {
		std::vector<ItemInstance> v13 = this->getItems();
		if(v13.size() == this->items.size()) {
			for(int32_t i = 0; i < v13.size(); ++i) {
				if(!ItemInstance::matches(&this->items[i], &v13[i])) {
					this->items[i] = v13[i];
					this->containerListener->slotChanged(this, i, this->items[i], this->isResultSlot(i));
				}
			}
		} else {
			this->items = v13;
			this->containerListener->refreshContainer(this, this->items);
		}
	}
}

void BaseContainerMenu::setListener(IContainerListener* a2) {
	this->containerListener = a2;
	if(a2) {
		a2->refreshContainer(this, this->items = std::move(this->getItems()));
	}
}
