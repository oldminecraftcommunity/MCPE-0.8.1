#pragma once
#include <_types.h>

template<typename T>
struct arrayWithLength
{
	T* array;
	int32_t size;
	arrayWithLength() {
	}
	arrayWithLength(int32_t size) {
		this->size = size;
		this->array = new T[size];
	}
	arrayWithLength(T* arr, int32_t size) {
		this->size = size;
		this->array = arr;
	}
};
