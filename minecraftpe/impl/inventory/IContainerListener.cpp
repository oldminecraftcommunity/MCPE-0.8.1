#include <inventory/IContainerListener.hpp>

IContainerListener::~IContainerListener() {
}
void IContainerListener::refreshContainer(BaseContainerMenu*, const std::vector<ItemInstance>) {
}
void IContainerListener::slotChanged(BaseContainerMenu*, int32_t, const ItemInstance&, bool_t) {
}
void IContainerListener::setContainerData(BaseContainerMenu*, int32_t, int32_t) {
}
