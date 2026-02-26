#pragma once
#include <_types.h>

struct DataLayer{
	int32_t layerSize;
	uint8_t* data;
	int32_t layerSize2;

	DataLayer(int32_t);
	int32_t get(int32_t, int32_t, int32_t);
	void set(int32_t, int32_t, int32_t, int32_t);
	~DataLayer();
};
