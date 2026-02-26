#pragma once
#include <_types.h>

template<typename T>
struct arrayWithLength
{
	T* array;
	int32_t size;
};
