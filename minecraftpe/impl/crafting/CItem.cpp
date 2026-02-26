#include <crafting/CItem.hpp>
CItem::ReqItem::ReqItem(const CItem::ReqItem& a2)
	: item(a2.item) {
	this->field_14 = a2.field_14;
}
CItem::ReqItem::ReqItem(ItemInstance& item, int count)
	: item(item) {
	this->field_14 = count;
}
CItem::CItem(const ItemInstance& a2, Recipe* a3, const std::string& a4)
	: field_0(a2) {
	this->recipe = a3;
	this->field_18 = a4;
	this->field_1C = a4;
	this->field_20 = 0;
	this->field_24 = 0;
	this->field_34 = 0;
}
CItem::~CItem() {

}
