#pragma once
#include <_types.h>
#include <string.h>

struct DataLayer{
	uint8_t* data;
	int32_t layerSize;
	int32_t layerSize2;

	DataLayer(int32_t size) {
		this->layerSize = size >> 1;
		this->data = new uint8_t[this->layerSize];
		memset(this->data, 0, this->layerSize);
		this->layerSize2 = this->layerSize;
	}
	int32_t get(int32_t x, int32_t y, int32_t z) {
		int32_t index = (x << 11) | (z << 7) | y;
		int ind = index >> 1;
		uint8_t res = (index & 1) == 0 ? (this->data[ind] & 0xf) : (this->data[ind] >> 4);
		return res;
	}
	void set(int32_t x, int32_t y, int32_t z, int32_t d) {
		int32_t index = (x << 11) | (z << 7) | y;
		int ind = index >> 1;

		if((index & 1) == 0) {
			this->data[ind] = (this->data[ind] & 0xf0) | (d & 0xf);
		} else {
			this->data[ind] = (this->data[ind] & 0x0f) | (d << 4);
		}
	}
	~DataLayer() {
		if (this->data) delete[] this->data;
	}
};
