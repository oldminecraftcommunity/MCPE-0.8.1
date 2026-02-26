#include <level/storage/DataLayer.hpp>
#include <string.h>

DataLayer::DataLayer(int32_t size){
	this->layerSize = size >> 1;
	this->data = new uint8_t[this->layerSize];
	memset(this->data, 0, this->layerSize);
	this->layerSize2 = this->layerSize;
}

DataLayer::~DataLayer(){
	if(this->data) delete[] this->data;
}

int32_t DataLayer::get(int32_t x, int32_t y, int32_t z){
	int32_t index = y | (x << 11) | (z << 7);
	uint8_t bt = this->data[index >> 1];
	if((index & 1) != 0) return bt >> 4;
	return bt & 0xf;
}

void DataLayer::set(int32_t x, int32_t y, int32_t z, int32_t d){
	int32_t index = y | (x << 11) | (z << 7);
	uint8_t bt = this->data[index >> 1];
	uint8_t res;
	if((index & 1) != 0) res = (bt & 0xf) | (16*d);
	else res = (d & 0xf) | (bt & 0xf0);

	this->data[index >> 1] = res;
}

