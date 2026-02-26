#include <entity/data/DataItem2.hpp>
#include <string>
#include <item/ItemInstance.hpp>
#include <math/Pos.hpp>

template<typename T>
DataItem2<T>::~DataItem2(){

}

template<> //signed char
DataItem2<int8_t>::DataItem2(int32_t id, int8_t v) {
	this->typeId = 0;
	_dataitem2_constructor(id, v);
}


template<> //short
DataItem2<int16_t>::DataItem2(int32_t id, int16_t v) {
	this->typeId = 1;
	_dataitem2_constructor(id, v);
}

template<> //int
DataItem2<int32_t>::DataItem2(int32_t id, int32_t v) {
	this->typeId = 2;
	_dataitem2_constructor(id, v);
}

template<> //float
DataItem2<float>::DataItem2(int32_t id, float v) {
	this->typeId = 3;
	_dataitem2_constructor(id, v);
}

template<> //string
DataItem2<std::string>::DataItem2(int32_t id, std::string v) {
	this->typeId = 4;
	_dataitem2_constructor(id, v);
}

template<> //ItemInstance
DataItem2<ItemInstance>::DataItem2(int32_t id, ItemInstance v) {
	this->typeId = 5;
	_dataitem2_constructor(id, v);
}

template<> //Pos
DataItem2<Pos>::DataItem2(int32_t id, Pos v) {
	this->typeId = 6;
	_dataitem2_constructor(id, v);
}
