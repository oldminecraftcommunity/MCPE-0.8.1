#include <FlyingItem.hpp>
FlyingItem::FlyingItem() {
}
FlyingItem::FlyingItem(const FlyingItem& a2) : field_0(a2.field_0) {
	this->field_18 = a2.field_18;
	this->field_20 = a2.field_20;
	this->field_24 = a2.field_24;
	this->field_28 = a2.field_28;
	this->field_2C = a2.field_2C;
	this->field_30 = a2.field_30;
}
