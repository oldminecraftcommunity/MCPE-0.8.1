#pragma once
#include <_types.h>

struct DataItem
{
	int32_t typeId, dataId;
	bool_t dirty;
	DataItem(int type, int data) : typeId(type), dataId(data), dirty(1){

	}
	virtual ~DataItem() {
	}
	virtual bool_t isDataEqual(const DataItem& a2) const {
		return this->dataId - a2.dataId + (this->dataId == a2.dataId) + a2.dataId - this->dataId;
	}
};
