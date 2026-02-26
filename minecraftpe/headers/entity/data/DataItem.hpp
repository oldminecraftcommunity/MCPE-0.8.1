#pragma once
#include <_types.h>

struct DataItem
{
	int32_t typeId, dataId;
	bool_t dirty;

	virtual ~DataItem();
	virtual bool_t isDataEqual(const DataItem&);
};
