#include <entity/data/DataItem.hpp>

bool_t DataItem::isDataEqual(const DataItem & a2){
	return this->dataId - a2.dataId + (this->dataId == a2.dataId) + a2.dataId - this->dataId;
}

DataItem::~DataItem() {
}
