#include <network/mco/MCOServerListItem.hpp>

MCOServerListItem::MCOServerListItem(const MCOServerListItem&);
MCOServerListItem::MCOServerListItem(MCOServerListItem&&);
MCOServerListItem::MCOServerListItem() {
	this->worldName = "My World";
	this->gamemodeName = "creative";
}
MCOServerListItem& MCOServerListItem::operator=(const MCOServerListItem& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->worldName = a2.worldName;
	this->field_C = a2.field_C;
	this->field_10 = a2.field_10;
	this->field_14 = a2.field_14;
	this->field_18 = a2.field_18;
	this->gamemodeName = a2.gamemodeName;
	this->field_20 = a2.field_20;
	this->field_2C = a2.field_2C;
	return *this;
}
MCOServerListItem& MCOServerListItem::operator=(MCOServerListItem&&);
MCOServerListItem::~MCOServerListItem() {
}
