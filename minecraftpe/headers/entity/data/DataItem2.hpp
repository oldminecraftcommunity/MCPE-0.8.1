#pragma once
#include <entity/data/DataItem.hpp>

//TODO define the typeId somehow else
#define _dataitem2_constructor(id, v) \
	this->dataId = id; \
	this->value = v; \
	this->dirty = 1;


template<typename T>
struct DataItem2: DataItem
{
	T value;

	DataItem2(int32_t id, T v);
	virtual ~DataItem2();
};
