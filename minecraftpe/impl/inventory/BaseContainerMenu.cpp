#include <inventory/BaseContainerMenu.hpp>
#include <inventory/IContainerListener.hpp>
#include <item/ItemInstance.hpp>

BaseContainerMenu::BaseContainerMenu(int32_t a2) {
	this->containerID = a2;
	this->field_0 = -1;
	this->containerListener = 0;
}
void BaseContainerMenu::broadcastChanges() {
	if(this->containerListener) {
		std::vector<ItemInstance> v13 = this->getItems();
		if(v13.size() == this->field_C.size()) {
			for(int32_t i = 0; i < v13.size(); ++i) {
				if(!ItemInstance::matches(&this->field_C[i], &v13[i])) {
					this->field_C[i] = v13[i];
					this->containerListener->slotChanged(this, i, this->field_C[i], this->isResultSlot(i));
				}
			}
		} else {
			this->field_C = v13;
			this->containerListener->refreshContainer(this, this->field_C);
		}
	}
}

void BaseContainerMenu::setListener(IContainerListener* a2) {
	this->containerListener = a2;
	if(a2) {
		a2->refreshContainer(this, this->field_C = std::move(this->getItems()));
	}
}
